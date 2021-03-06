#ifndef RBCZMQ_LOOP_H
#define RBCZMQ_LOOP_H

#define ZMQ_LOOP_DESTROYED 0x01

typedef struct {
    zloop_t  *loop;
    int flags;
    bool verbose;
    bool running;
    VALUE items; /* pollitem and timer objects we need to keep from being garbage collected. */
} zmq_loop_wrapper;

#define ZmqAssertLoop(obj) ZmqAssertType(obj, rb_cZmqLoop, "ZMQ::Loop")
#define ZmqGetLoop(obj) \
    zmq_loop_wrapper *loop = NULL; \
    ZmqAssertLoop(obj); \
    Data_Get_Struct(obj, zmq_loop_wrapper, loop); \
    if (!loop) rb_raise(rb_eTypeError, "uninitialized ZMQ loop!"); \
    if (loop->flags & ZMQ_LOOP_DESTROYED) rb_raise(rb_eZmqError, "ZMQ::Loop instance %p has been destroyed by the ZMQ framework", (void *)obj);

VALUE rb_czmq_pollitem_set_verbose(VALUE obj, VALUE level);
void _init_rb_czmq_loop();

#endif
