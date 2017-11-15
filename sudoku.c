#ifndef queue_h
#define queue_h
#include <stddef.h>

// Defines a circular buffer which acts as a FIFO queue.
typedef struct queue_t
{
    int    size;
    int    next;
    int    capacity;
    void** data;
} queue_t;

// Allocates and returns a new queue. The capacity specifies the maximum
// number of items that can be in the queue at one time. A capacity greater
// than INT_MAX / sizeof(void*) is considered an error. Returns NULL if
// initialization failed.
queue_t* queue_init(size_t capacity);

// Releases the queue resources.
void queue_dispose(queue_t* queue);

// Enqueues an item in the queue. Returns 0 if the add succeeded or -1 if it
// failed. If -1 is returned, errno will be set.
int queue_add(queue_t* queue, void* value);

// Dequeues an item from the head of the queue. Returns NULL if the queue is
// empty.
void* queue_remove(queue_t* queue);

// Returns, but does not remove, the head of the queue. Returns NULL if the
// queue is empty.
void* queue_peek(queue_t*);

#endif
#ifndef chan_h
#define chan_h

#include <pthread.h>
#include <stdint.h>

#include "queue.h"


// Defines a thread-safe communication pipe. Channels are either buffered or
// unbuffered. An unbuffered channel is synchronized. Receiving on either type
// of channel will block until there is data to receive. If the channel is
// unbuffered, the sender blocks until the receiver has received the value. If
// the channel is buffered, the sender only blocks until the value has been
// copied to the buffer, meaning it will block if the channel is full.
typedef struct chan_t
{
    // Buffered channel properties
    queue_t*         queue;
    
    // Unbuffered channel properties
    pthread_mutex_t  r_mu;
    pthread_mutex_t  w_mu;
    void*            data;

    // Shared properties
    pthread_mutex_t  m_mu;
    pthread_cond_t   r_cond;
    pthread_cond_t   w_cond;
    int              closed;
    int              r_waiting;
    int              w_waiting;
} chan_t;

// Allocates and returns a new channel. The capacity specifies whether the
// channel should be buffered or not. A capacity of 0 will create an unbuffered
// channel. Sets errno and returns NULL if initialization failed.
chan_t* chan_init(size_t capacity);

// Releases the channel resources.
void chan_dispose(chan_t* chan);

// Once a channel is closed, data cannot be sent into it. If the channel is
// buffered, data can be read from it until it is empty, after which reads will
// return an error code. Reading from a closed channel that is unbuffered will
// return an error code. Closing a channel does not release its resources. This
// must be done with a call to chan_dispose. Returns 0 if the channel was
// successfully closed, -1 otherwise.
int chan_close(chan_t* chan);

// Returns 0 if the channel is open and 1 if it is closed.
int chan_is_closed(chan_t* chan);

// Sends a value into the channel. If the channel is unbuffered, this will
// block until a receiver receives the value. If the channel is buffered and at
// capacity, this will block until a receiver receives a value. Returns 0 if
// the send succeeded or -1 if it failed.
int chan_send(chan_t* chan, void* data);

// Receives a value from the channel. This will block until there is data to
// receive. Returns 0 if the receive succeeded or -1 if it failed.
int chan_recv(chan_t* chan, void** data);

// Returns the number of items in the channel buffer. If the channel is
// unbuffered, this will return 0.
int chan_size(chan_t* chan);

// A select statement chooses which of a set of possible send or receive
// operations will proceed. The return value indicates which channel's
// operation has proceeded. If more than one operation can proceed, one is
// selected randomly. If none can proceed, -1 is returned. Select is intended
// to be used in conjunction with a switch statement. In the case of a receive
// operation, the received value will be pointed to by the provided pointer. In
// the case of a send, the value at the same index as the channel will be sent.
int chan_select(chan_t* recv_chans[], int recv_count, void** recv_out,
    chan_t* send_chans[], int send_count, void* send_msgs[]);

// Typed interface to send/recv chan.
int chan_send_int32(chan_t*, int32_t);
int chan_send_int64(chan_t*, int64_t);
#if ULONG_MAX == 4294967295UL
# define chan_send_int(c, d) chan_send_int64(c, d)
#else
# define chan_send_int(c, d) chan_send_int32(c, d)
#endif
int chan_send_double(chan_t*, double);
int chan_send_buf(chan_t*, void*, size_t);
int chan_recv_int32(chan_t*, int32_t*);
int chan_recv_int64(chan_t*, int64_t*);
#if ULONG_MAX == 4294967295UL
# define chan_recv_int(c, d) chan_recv_int64(c, d)
#else
# define chan_recv_int(c, d) chan_recv_int32(c, d)
#endif
int chan_recv_double(chan_t*, double*);
int chan_recv_buf(chan_t*, void*, size_t);

#endif
#ifndef PARSE_H
#define PARSE_H

char** str_split(char* a_str, char a_delim);
void ParseFile(int sudokuBoard[9][9]);

#endif//
// Created by Jeffrey  Booher-Kaeding on 11/12/17.
//

#ifndef CS450_HW3_BOARDVALIDATE_H
#define CS450_HW3_BOARDVALIDATE_H

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "chan.h"
// Struct for thread params
// https://stackoverflow.com/a/16230944/4730779
struct readThreadParams {
    int (*sudokuBoard)[9];
    int num;
    chan_t* validChan
    ;
    char* error;
};
bool ValidateBoard(int sudokuBoard[9][9]);

void* validateRow(void* params);

void* validateCol(void* params);

void* validateBox(void* params);

bool testArray(bool const * test);

#endif //CS450_HW3_BOARDVALIDATE_H
#include <stdio.h>
#include "parsetools.h"
#include "boardvalidate.h"


int main(int argc, char *argv[]) {
	int sudokuBoard[9][9];
	ParseFile(sudokuBoard); // Parsefile stores result in sudokuboard
	bool result = ValidateBoard(sudokuBoard);
	if (!result){
		printf( "The input is not a valid Sudoku\n");
	}
	else{
		printf("You did it kiddo, you valid Sudoku\n");
	}
	return 0;
}
#define _GNU_SOURCE

#ifdef __APPLE__
#define _XOPEN_SOURCE
#endif

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#if defined(_WIN32) && !defined(ENOBUFS)
#include <winsock.h>
#define ENOBUFS WSAENOBUFS
#endif

// Returns 0 if the queue is not at capacity. Returns 1 otherwise.
static inline int queue_at_capacity(queue_t* queue)
{
    return queue->size >= queue->capacity;
}

// Allocates and returns a new queue. The capacity specifies the maximum
// number of items that can be in the queue at one time. A capacity greater
// than INT_MAX / sizeof(void*) is considered an error. Returns NULL if
// initialization failed.
queue_t* queue_init(size_t capacity)
{
    if (capacity > INT_MAX / sizeof(void*))
    {
        errno = EINVAL;
        return NULL;
    }

    queue_t* queue = (queue_t*) malloc(sizeof(queue_t));
    void**   data  = (void**) malloc(capacity * sizeof(void*));
    if (!queue || !data)
    {
        // In case of free(NULL), no operation is performed.
        free(queue);
        free(data);   
        errno = ENOMEM;
        return NULL;
    }

    queue->size = 0;
    queue->next = 0;
    queue->capacity = capacity;
    queue->data = data;
    return queue;
}

// Releases the queue resources.
void queue_dispose(queue_t* queue)
{
    free(queue->data);
    free(queue);
}

// Enqueues an item in the queue. Returns 0 is the add succeeded or -1 if it
// failed. If -1 is returned, errno will be set.
int queue_add(queue_t* queue, void* value)
{
    if (queue_at_capacity(queue))
    {
        errno = ENOBUFS;
        return -1;
    }

    int pos = queue->next + queue->size;
    if (pos >= queue->capacity)
    {
       pos -= queue->capacity;
    }

    queue->data[pos] = value;

    queue->size++;
    return 0;
}

// Dequeues an item from the head of the queue. Returns NULL if the queue is
// empty.
void* queue_remove(queue_t* queue)
{
    void* value = NULL;

    if (queue->size > 0)
    {
        value = queue->data[queue->next];
        queue->next++;
        queue->size--;
        if (queue->next >= queue->capacity)
        {
            queue->next -= queue->capacity;
        }
    }

    return value;
}

// Returns, but does not remove, the head of the queue. Returns NULL if the
// queue is empty.
void* queue_peek(queue_t* queue)
{
    return queue->size ? queue->data[queue->next] : NULL;
}
#define _GNU_SOURCE
#undef __STRICT_ANSI__

#ifdef __APPLE__
#define _XOPEN_SOURCE
#endif

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include "chan.h"
#include "queue.h"

#ifdef _WIN32
#include <windows.h>
#define CLOCK_REALTIME 0
static int clock_gettime (int __attribute__((__unused__)) clockid, struct timespec *tp) {
    FILETIME ft;
    ULARGE_INTEGER t64;
    GetSystemTimeAsFileTime (&ft);
    t64.LowPart = ft.dwLowDateTime;
    t64.HighPart = ft.dwHighDateTime;
    tp->tv_sec = t64.QuadPart / 10000000 - 11644473600;
    tp->tv_nsec = t64.QuadPart % 10000000 * 100;
    return 0;
}
#endif

static int buffered_chan_init(chan_t* chan, size_t capacity);
static int buffered_chan_send(chan_t* chan, void* data);
static int buffered_chan_recv(chan_t* chan, void** data);

static int unbuffered_chan_init(chan_t* chan);
static int unbuffered_chan_send(chan_t* chan, void* data);
static int unbuffered_chan_recv(chan_t* chan, void** data);

static int chan_can_recv(chan_t* chan);
static int chan_can_send(chan_t* chan);
static int chan_is_buffered(chan_t* chan);

void current_utc_time(struct timespec *ts) {
#ifdef __MACH__ 
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, ts);
#endif
}

// Allocates and returns a new channel. The capacity specifies whether the
// channel should be buffered or not. A capacity of 0 will create an unbuffered
// channel. Sets errno and returns NULL if initialization failed.
chan_t* chan_init(size_t capacity)
{
    chan_t* chan = (chan_t*) malloc(sizeof(chan_t));
    if (!chan)
    {
        errno = ENOMEM;
        return NULL;
    }

    if (capacity > 0)
    {
        if (buffered_chan_init(chan, capacity) != 0)
        {
            free(chan);
            return NULL;
        }
    }
    else
    {
        if (unbuffered_chan_init(chan) != 0)
        {
            free(chan);
            return NULL;
        }
    }
    
    return chan;
}

static int buffered_chan_init(chan_t* chan, size_t capacity)
{
    queue_t* queue = queue_init(capacity);
    if (!queue)
    {
        return -1;
    }

    if (unbuffered_chan_init(chan) != 0)
    {
        queue_dispose(queue);
        return -1;
    }
    
    chan->queue = queue;
    return 0;
}

static int unbuffered_chan_init(chan_t* chan)
{
    if (pthread_mutex_init(&chan->w_mu, NULL) != 0)
    {
        return -1;
    }

    if (pthread_mutex_init(&chan->r_mu, NULL) != 0)
    {
        pthread_mutex_destroy(&chan->w_mu);
        return -1;
    }

    if (pthread_mutex_init(&chan->m_mu, NULL) != 0)
    {
        pthread_mutex_destroy(&chan->w_mu);
        pthread_mutex_destroy(&chan->r_mu);
        return -1;
    }

    if (pthread_cond_init(&chan->r_cond, NULL) != 0)
    {
        pthread_mutex_destroy(&chan->m_mu);
        pthread_mutex_destroy(&chan->w_mu);
        pthread_mutex_destroy(&chan->r_mu);
        return -1;
    }

    if (pthread_cond_init(&chan->w_cond, NULL) != 0)
    {
        pthread_mutex_destroy(&chan->m_mu);
        pthread_mutex_destroy(&chan->w_mu);
        pthread_mutex_destroy(&chan->r_mu);
        pthread_cond_destroy(&chan->r_cond);
        return -1;
    }

    chan->closed = 0;
    chan->r_waiting = 0;
    chan->w_waiting = 0;
    chan->queue = NULL;
    chan->data = NULL;
    return 0;
}

// Releases the channel resources.
void chan_dispose(chan_t* chan)
{
    if (chan_is_buffered(chan))
    {
        queue_dispose(chan->queue);
    }

    pthread_mutex_destroy(&chan->w_mu);
    pthread_mutex_destroy(&chan->r_mu);

    pthread_mutex_destroy(&chan->m_mu);
    pthread_cond_destroy(&chan->r_cond);
    pthread_cond_destroy(&chan->w_cond);
    free(chan);
}

// Once a channel is closed, data cannot be sent into it. If the channel is
// buffered, data can be read from it until it is empty, after which reads will
// return an error code. Reading from a closed channel that is unbuffered will
// return an error code. Closing a channel does not release its resources. This
// must be done with a call to chan_dispose. Returns 0 if the channel was
// successfully closed, -1 otherwise. If -1 is returned, errno will be set.
int chan_close(chan_t* chan)
{
    int success = 0;
    pthread_mutex_lock(&chan->m_mu);
    if (chan->closed)
    {
        // Channel already closed.
        success = -1;
        errno = EPIPE;
    }
    else
    {
        // Otherwise close it.
        chan->closed = 1;
        pthread_cond_broadcast(&chan->r_cond);
        pthread_cond_broadcast(&chan->w_cond);
    }
    pthread_mutex_unlock(&chan->m_mu);
    return success;
}

// Returns 0 if the channel is open and 1 if it is closed.
int chan_is_closed(chan_t* chan)
{
    pthread_mutex_lock(&chan->m_mu);
    int closed = chan->closed;
    pthread_mutex_unlock(&chan->m_mu);
    return closed;
}

// Sends a value into the channel. If the channel is unbuffered, this will
// block until a receiver receives the value. If the channel is buffered and at
// capacity, this will block until a receiver receives a value. Returns 0 if
// the send succeeded or -1 if it failed. If -1 is returned, errno will be set.
int chan_send(chan_t* chan, void* data)
{
    if (chan_is_closed(chan))
    {
        // Cannot send on closed channel.
        errno = EPIPE;
        return -1;
    }

    return chan_is_buffered(chan) ?
        buffered_chan_send(chan, data) :
        unbuffered_chan_send(chan, data);
}

// Receives a value from the channel. This will block until there is data to
// receive. Returns 0 if the receive succeeded or -1 if it failed. If -1 is
// returned, errno will be set.
int chan_recv(chan_t* chan, void** data)
{
    return chan_is_buffered(chan) ?
        buffered_chan_recv(chan, data) :
        unbuffered_chan_recv(chan, data);
}

static int buffered_chan_send(chan_t* chan, void* data)
{
    pthread_mutex_lock(&chan->m_mu);
    while (chan->queue->size == chan->queue->capacity)
    {
        // Block until something is removed.
        chan->w_waiting++;
        pthread_cond_wait(&chan->w_cond, &chan->m_mu);
        chan->w_waiting--;
    }

    int success = queue_add(chan->queue, data);

    if (chan->r_waiting > 0)
    {
        // Signal waiting reader.
        pthread_cond_signal(&chan->r_cond);
    }

    pthread_mutex_unlock(&chan->m_mu);
    return success;
}

static int buffered_chan_recv(chan_t* chan, void** data)
{
    pthread_mutex_lock(&chan->m_mu);
    while (chan->queue->size == 0)
    {
        if (chan->closed)
        {
            pthread_mutex_unlock(&chan->m_mu);
            errno = EPIPE;
            return -1;
        }

        // Block until something is added.
        chan->r_waiting++;
        pthread_cond_wait(&chan->r_cond, &chan->m_mu);
        chan->r_waiting--;
    }

    void* msg = queue_remove(chan->queue);
    if (data)
    {
        *data = msg;
    }

    if (chan->w_waiting > 0)
    {
        // Signal waiting writer.
        pthread_cond_signal(&chan->w_cond);
    }

    pthread_mutex_unlock(&chan->m_mu);
    return 0;
}

static int unbuffered_chan_send(chan_t* chan, void* data)
{
    pthread_mutex_lock(&chan->w_mu);
    pthread_mutex_lock(&chan->m_mu);

    if (chan->closed)
    {
        pthread_mutex_unlock(&chan->m_mu);
        pthread_mutex_unlock(&chan->w_mu);
        errno = EPIPE;
        return -1;
    }

    chan->data = data;
    chan->w_waiting++;

    if (chan->r_waiting > 0)
    {
        // Signal waiting reader.
        pthread_cond_signal(&chan->r_cond);
    }

    // Block until reader consumed chan->data.
    pthread_cond_wait(&chan->w_cond, &chan->m_mu);

    pthread_mutex_unlock(&chan->m_mu);
    pthread_mutex_unlock(&chan->w_mu);
    return 0;
}

static int unbuffered_chan_recv(chan_t* chan, void** data)
{
    pthread_mutex_lock(&chan->r_mu);
    pthread_mutex_lock(&chan->m_mu);

    while (!chan->closed && !chan->w_waiting)
    {
        // Block until writer has set chan->data.
        chan->r_waiting++;
        pthread_cond_wait(&chan->r_cond, &chan->m_mu);
        chan->r_waiting--;
    }

    if (chan->closed)
    {
        pthread_mutex_unlock(&chan->m_mu);
        pthread_mutex_unlock(&chan->r_mu);
        errno = EPIPE;
        return -1;
    }

    if (data)
    {
        *data = chan->data;
    }
    chan->w_waiting--;

    // Signal waiting writer.
    pthread_cond_signal(&chan->w_cond);

    pthread_mutex_unlock(&chan->m_mu);
    pthread_mutex_unlock(&chan->r_mu);
    return 0;
}

// Returns the number of items in the channel buffer. If the channel is
// unbuffered, this will return 0.
int chan_size(chan_t* chan)
{
    int size = 0;
    if (chan_is_buffered(chan))
    {
        pthread_mutex_lock(&chan->m_mu);
        size = chan->queue->size;
        pthread_mutex_unlock(&chan->m_mu);
    }
    return size;
}

typedef struct
{
    int     recv;
    chan_t* chan;
    void*   msg_in;
    int     index;
} select_op_t;

// A select statement chooses which of a set of possible send or receive
// operations will proceed. The return value indicates which channel's
// operation has proceeded. If more than one operation can proceed, one is
// selected randomly. If none can proceed, -1 is returned. Select is intended
// to be used in conjunction with a switch statement. In the case of a receive
// operation, the received value will be pointed to by the provided pointer. In
// the case of a send, the value at the same index as the channel will be sent.
int chan_select(chan_t* recv_chans[], int recv_count, void** recv_out,
    chan_t* send_chans[], int send_count, void* send_msgs[])
{
    // TODO: Add support for blocking selects.

    select_op_t candidates[recv_count + send_count];
    int count = 0;
    int i;

    // Determine receive candidates.
    for (i = 0; i < recv_count; i++)
    {
        chan_t* chan = recv_chans[i];
        if (chan_can_recv(chan))
        {
            select_op_t op;
            op.recv = 1;
            op.chan = chan;
            op.index = i;
            candidates[count++] = op;
        }
    }

    // Determine send candidates.
    for (i = 0; i < send_count; i++)
    {
        chan_t* chan = send_chans[i];
        if (chan_can_send(chan))
        {
            select_op_t op;
            op.recv = 0;
            op.chan = chan;
            op.msg_in = send_msgs[i];
            op.index = i + recv_count;
            candidates[count++] = op;
        }
    }
    
    if (count == 0)
    {
        return -1;
    }

    // Seed rand using current time in nanoseconds.
    struct timespec ts;
    current_utc_time(&ts);
    srand(ts.tv_nsec);

    // Select candidate and perform operation.
    select_op_t select = candidates[rand() % count];
    if (select.recv && chan_recv(select.chan, recv_out) != 0)
    {
        return -1;
    }
    else if (!select.recv && chan_send(select.chan, select.msg_in) != 0)
    {
        return -1;
    }

    return select.index;
}

static int chan_can_recv(chan_t* chan)
{
    if (chan_is_buffered(chan))
    {
        return chan_size(chan) > 0;
    }

    pthread_mutex_lock(&chan->m_mu);
    int sender = chan->w_waiting > 0;
    pthread_mutex_unlock(&chan->m_mu);
    return sender;
}

static int chan_can_send(chan_t* chan)
{
    int send;
    if (chan_is_buffered(chan))
    {
        // Can send if buffered channel is not full.
        pthread_mutex_lock(&chan->m_mu);
        send = chan->queue->size < chan->queue->capacity;
        pthread_mutex_unlock(&chan->m_mu);
    }
    else
    {
        // Can send if unbuffered channel has receiver.
        pthread_mutex_lock(&chan->m_mu);
        send = chan->r_waiting > 0;
        pthread_mutex_unlock(&chan->m_mu);
    }

    return send;
}

static int chan_is_buffered(chan_t* chan)
{
    return chan->queue != NULL;
}

int chan_send_int32(chan_t* chan, int32_t data)
{
    int32_t* wrapped = malloc(sizeof(int32_t));
    if (!wrapped)
    {
        return -1;
    }

    *wrapped = data;

    int success = chan_send(chan, wrapped);
    if (success != 0)
    {
        free(wrapped);
    }

    return success;
}

int chan_recv_int32(chan_t* chan, int32_t* data)
{
    int32_t* wrapped = NULL;
    int success = chan_recv(chan, (void*) &wrapped);
    if (wrapped != NULL)
    {
        *data = *wrapped;
        free(wrapped);
    }

    return success;
}

int chan_send_int64(chan_t* chan, int64_t data)
{
    int64_t* wrapped = malloc(sizeof(int64_t));
    if (!wrapped)
    {
        return -1;
    }

    *wrapped = data;

    int success = chan_send(chan, wrapped);
    if (success != 0)
    {
        free(wrapped);
    }

    return success;
}

int chan_recv_int64(chan_t* chan, int64_t* data)
{
    int64_t* wrapped = NULL;
    int success = chan_recv(chan, (void*) &wrapped);
    if (wrapped != NULL)
    {
        *data = *wrapped;
        free(wrapped);
    }

    return success;
}

int chan_send_double(chan_t* chan, double data)
{
    double* wrapped = malloc(sizeof(double));
    if (!wrapped)
    {
        return -1;
    }

    *wrapped = data;

    int success = chan_send(chan, wrapped);
    if (success != 0)
    {
        free(wrapped);
    }

    return success;
}

int chan_recv_double(chan_t* chan, double* data)
{
    double* wrapped = NULL;
    int success = chan_recv(chan, (void*) &wrapped);
    if (wrapped != NULL)
    {
        *data = *wrapped;
        free(wrapped);
    }

    return success;
}

int chan_send_buf(chan_t* chan, void* data, size_t size)
{
    void* wrapped = malloc(size);
    if (!wrapped)
    {
        return -1;
    }

    memcpy(wrapped, data, size);

    int success = chan_send(chan, wrapped);
    if (success != 0)
    {
        free(wrapped);
    }

    return success;
}

int chan_recv_buf(chan_t* chan, void* data, size_t size)
{
    void* wrapped = NULL;
    int success = chan_recv(chan, (void*) &wrapped);
    if (wrapped != NULL)
    {
        memcpy(data, wrapped, size);
        free(wrapped);
    }

    return success;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Splits a string by token
// https://stackoverflow.com/a/9210560/4951118
char** str_split(char* a_str, char a_delim) {
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

#define BUF_SIZE 512
#define BUF_MIN 128
	
void ParseFile(int sudokuBoard[9][9]) {
	// Read file into string - https://stackoverflow.com/a/7856790/4951118
	char *file_contents, *p;
    int len, remain, n, size;

    size = BUF_SIZE;
    file_contents = malloc(size);
    len = 0;
    remain = size;
    while (!feof(stdin)) {
		if (remain <= BUF_MIN) {
			remain += size;
			size *= 2;
			p = realloc(file_contents, size);
			if (p == NULL) {
				free(file_contents);
				return;
			}
			file_contents = p;
		}

		fgets(file_contents + len, remain, stdin);
		n = strlen(file_contents + len);
		len += n;
		remain -= n;
	}
	
	// Break string into rows by newline
	char** rowsAsStrings = str_split(file_contents, '\n');
	
	// Break rows into chars by space
	char** rowsOfElements[9]; // array or arrays of character arrays
	for(int i=0; i < 9; i++) {
		rowsOfElements[i] = str_split(rowsAsStrings[i], ' ');
	}
	
	// rowsOfElements is now a 2D grid of char pointers, but we want those char pointers to be ints
	// Convert chars to ints
	for(int i=0; i < 9; i++) {
		for(int j=0; j < 9; j++) {
			// The 0 is to get the first character (which should be the only one except null term)
			// Minus 0 converts to int - https://stackoverflow.com/a/628778/4951118
			sudokuBoard[i][j] = rowsOfElements[i][j][0] - '0';
		}
	}
	
	free(file_contents);
}
#include "boardvalidate.h"

bool ValidateBoard(int sudokuBoard[9][9]) {
//This is the mother function board
    chan_t* valid;
    valid = chan_init(27);
    pthread_t th[27];
	//printf("Summoning workers\n");

    //
    //
    for (int i=0; i<9; i++) {
        char* strR = malloc(100);
        char* strC = malloc(100);
        char* strB = malloc(100);
        sprintf(strR,"Row %d",i);
		
		// Making sure every thread has a unique struct
		struct readThreadParams* readParams = malloc(sizeof(struct readThreadParams));
		(*readParams).sudokuBoard = sudokuBoard;
		(*readParams).validChan = valid;
        (*readParams).num = i;
        (*readParams).error = strR;
        //validateRow
        pthread_create(&th[i],NULL,validateRow,readParams);

        sprintf(strC,"Col %d",i);
		readParams = malloc(sizeof(struct readThreadParams));
		(*readParams).sudokuBoard = sudokuBoard;
		(*readParams).validChan = valid;
        (*readParams).num = i;
        (*readParams).error = strC;
        //validateCol
		// Generating the strings the channels will return
        pthread_create(&th[i+9],NULL,validateCol,readParams);
		char *tmp;
        switch(i+1) {
            case 1:
				tmp = "The left top";
                strcpy(strB, tmp);
                break;
            case 2:
                tmp = "The middle top";
                strcpy(strB, tmp);
                break;
            case 3:
                tmp = "The right top";
                strcpy(strB, tmp);
                break;
            case 4:
                tmp = "The left middle";
                strcpy(strB, tmp);
                break;
            case 5:
                tmp = "The middle middle";
                strcpy(strB, tmp);
                break;
            case 6:
                tmp = "The right middle";
                strcpy(strB, tmp);
                break;
            case 7:
                tmp = "The left bottom";
                strcpy(strB, tmp);
                break;
            case 8:
                tmp = "The middle bottom";
                strcpy(strB, tmp);
                break;
            case 9:
                tmp = "The right bottom";
                strcpy(strB, tmp);
                break;
            default:
                tmp = "invalid bounds";
                strcpy(strB, tmp);
        }
        readParams = malloc(sizeof(struct readThreadParams));
		(*readParams).sudokuBoard = sudokuBoard;
		(*readParams).validChan = valid;
        (*readParams).num = i;
        (*readParams).error = strB;
        //validateBox
        pthread_create(&th[i+18],NULL,validateBox,readParams);
    }
    int i = 0;
    bool work = true;
    void* error_string;
    while ( chan_recv(valid, &error_string) == 0)
    {
        if (error_string != NULL) {
            printf("%s doesn't have the requred values.\n", (char*)error_string);
            work = false;
        }
		free(error_string);
        i++;
        if (i >= 27){
            break;
        }
    }
	
	chan_dispose(valid);
    return work;
}

void* freedom(struct readThreadParams *params) {
	free(params);
}

void* validateRow(void* params) {
	struct readThreadParams *params1 = params;
    //create a bool array for comparison
    bool test[9] = { false };

    for (int i = 0; i < 9; i++){
        //check board[i][num]
        test[params1->sudokuBoard[i][params1->num]-1] = true;
    }

    //check for valid
    bool isValid = testArray(test);
    //if not valid tell the main the error, otherwise tell it null.
    if (!isValid) {
        chan_send(params1->validChan, params1->error);
    }
    else {
        chan_send(params1->validChan, NULL);
    }
    //return a null pointer to make CLion happy.
	freedom(params);
    return NULL;
}



void* validateCol(void* params) {
    struct readThreadParams *params1 = params;
    //create a bool array for comparison
    bool test[9] = { false };

    for (int j = 0; j < 9; j++){
        //check board[n][i]
        test[params1->sudokuBoard[params1->num][j]-1] = true;
    }

    //check for valid
    bool isValid = testArray(test);
    //if not valid tell the main the error, otherwise tell it null.
    if (!isValid) {
        chan_send(params1->validChan, params1->error);
    }
    else {
        chan_send(params1->validChan, NULL);
    }
    //return a null pointer to make CLion happy.
	freedom(params);
    return NULL;
}


void* validateBox(void* params) {
    struct readThreadParams *params1 = params;
    //create a bool array for comparison
    bool test[9] = {false};
    //we use this to index in the 9x9 grid
    //we use (num/3)*3 for the int divisor, and for the rows
    int base_row = 3*(params1->num / 3);
    //we use mod three for the cols
    int base_col = 3*(params1->num % 3);
    //we then go in a 3x3 box with the base being the top left.
    for ( int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            test[(params1->sudokuBoard[base_col+i][base_row+j])-1] = true;
        }
    }

    //check for valid
    bool isValid = testArray(test);
    //if not valid tell the main the error, otherwise tell it null.
    if (!isValid) {
        chan_send(params1->validChan, params1->error);
    }
    else {
        chan_send(params1->validChan, NULL);
    }
    //return a null pointer to make CLion happy.
	freedom(params);
    return NULL;
}

bool testArray(bool const *  test) {
    //const *
    //https://stackoverflow.com/a/1143272/4730779

    //lets take the list of bools,
    // look for any cases where a number isn't present aka false
    for (int k = 0; k < 9; k++) {
        if (!test[k])
            //if we are missing a number return false to print the error
            return false;
    }
    //else we can return true
    return true;
}
