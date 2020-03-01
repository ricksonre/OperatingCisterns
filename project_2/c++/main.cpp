#include <iostream>
#include <pthread.h>
#include <queue>
#include <vector>
#include <random>
#include <ctime>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class request
{
public:
    int id;
    int length;

    request() : id{-1}, length{0} {}
    request(int id, int length) : id{id}, length{length} {}
};

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class bounded_buffer
{
private:
    std::queue<request> buffer;
    pthread_mutex_t process_lock = PTHREAD_MUTEX_INITIALIZER;

public:
    void add_request(request r);
    request process_request();
} buffer;

void bounded_buffer::add_request(request r)
{
    pthread_mutex_lock(&process_lock);

    buffer.push(r);

    pthread_mutex_unlock(&process_lock);
}

request bounded_buffer::process_request()
{
    request r;

    pthread_mutex_lock(&process_lock);

    if (!buffer.empty())
        r = buffer.back();
    buffer.pop();

    pthread_mutex_unlock(&process_lock);

    return r;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void *master(void *max)
{
    int id = 0;
    std::default_random_engine random;
    std::uniform_int_distribution<int> range(1, *(int *)max);

    while (true)
    {
        int length = range(random);

        std::cout << " Producer: creating request with id: " << id << " and length:" << length << " seconds, current time is "
                  << clock() << std::endl;

        buffer.add_request(request(id, length));
        id++;

        int t = range(random);
        std::cout << "Producer: me tired sleep for " << t << std::endl;
        sleep(t);
    }
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void *slave(void *ptr)
{
    while (true)
    {
        request r = buffer.process_request();

        if (r.id != -1)
        {
            std::cout << " Consumer " << pthread_self() << ": assigned request ID " << r.id
                      << ", processing request for the next:" << r.length << " seconds, current time is "
                      << clock() << std::endl;

            sleep(r.length);

            std::cout << " Consumer " << pthread_self() << ": completed request " << r.id << " at time" << clock() << std::endl;
        }
        else
        {
            std::cout << " Consumer " << pthread_self() << " no request to process"
                      << " at time" << clock() << std::endl;
        }
    }
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

int main()
{

    int n_slaves; //number of slave threads
    int *max = new int;     //max time to produce new request

    std::cout << "Enter the number of threads: ";
    std::cin >> n_slaves;
    std::cout << "Enter the max time to produce a new request: ";
    std::cin >> *max;
    std::cout << std::endl;

    pthread_t master_thread;
    std::vector<pthread_t> slave_threads(n_slaves); //instantiate master class

    pthread_create(&master_thread, NULL, master, (void *)max); //creates the master thread and executes it
    for (int i = 0; i < n_slaves; i++)                         //
        pthread_create(&slave_threads[i], NULL, slave, NULL);  //create n slave threads and execute them

    pthread_join(master_thread, NULL); // no clue what this does
    for (int i = 0; i < n_slaves; i++)
        pthread_join(slave_threads[i], NULL);
}