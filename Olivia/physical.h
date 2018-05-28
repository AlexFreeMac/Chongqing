#ifndef PHYSICAL_H
#define PHYSICAL_H


extern "C"
{
    typedef void OliviaDecoded(unsigned char * buffer, int bufferlen);
    void * init_player();
    void * init_recorder(OliviaDecoded *onDecoded);
    void free_olivia(void * obj);
    bool play(void * player, unsigned char * buffer, int bufferlen);
    bool start_record(void * recorder);
    bool is_running(void * obj);
    void stop_olivia(void * obj);
}

#endif // PHYSICAL_H
