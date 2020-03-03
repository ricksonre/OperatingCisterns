#include <iostream>
#include <pthread.h>
#include <queue>
#include <vector>
#include <random>
#include <ctime>
#include <unistd.h>//including required libraries

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class request//declaring the request class, (will be used for the requests created and consumed)
{
public:
    int id;
    int length;//setting up variables & constructors

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
    pthread_mutex_t process_lock;//private var declerations for bounded_buffer
	pthread_mutex_t bound_lock;//  including mutexes, conditional vars & int n
    pthread_cond_t cond;
	
	int n;

public:
	void set_bounds(int n);
	bounded_buffer();
    void add_request(request r);//declaring methods
    request process_request();
} buffer;

bounded_buffer::bounded_buffer()
{
	process_lock = PTHREAD_MUTEX_INITIALIZER;
	bound_lock = PTHREAD_MUTEX_INITIALIZER;
    cond = PTHREAD_COND_INITIALIZER;
}

void bounded_buffer::set_bounds(int n)//set bounds method
{
	this->n = n;//sets n to given n in method call
}

void bounded_buffer::add_request(request r)//method to add a request to the buffer
{
	if(buffer.size() >= (n-1))//if method is one off of full, or full
		pthread_mutex_lock(&bound_lock);//acquire the bound_lock mutex
	
	pthread_mutex_lock(&process_lock);//acquire process lock mutex (general add and pop lock)

    buffer.push(r);//add r to buffer
    pthread_cond_signal(&cond);//signal the conditional that allows a slave to awaken
	
    pthread_mutex_unlock(&process_lock);//release process lock
}

request bounded_buffer::process_request()//pop/get a request method
{
    request r;//declare an r var

    
    pthread_mutex_lock(&process_lock);//acquire the general process lock for all buffer ops
    pthread_cond_wait(&cond, &process_lock);//wait on conditional var to be available
    r = buffer.back();//sets r to the back of the buffer
    buffer.pop();//pop back of buffer, removing the request

    pthread_mutex_unlock(&process_lock);//relinquish mutex for process lock
    pthread_mutex_unlock(&bound_lock);// unlock bound lock which will allow a master which was stopped 
                                      // by a full buffer to continue

    return r;//return request r
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void *master(void *max)//master thread method
{
    int id = 0;//id = 0 for master thread
    std::default_random_engine random;
    std::uniform_int_distribution<int> range(1, *(int *)max);//setting random guidelines

    while (true)//master runs forever
    {
        int length = range(random);//request length randomized

        std::cout << " Producer: creating request with id: " << id << " and length:" << length << " seconds, current time is "
                  << clock() << std::endl;
                  //outputs what the master thread is producing as a request
                  //as well as system time when it was done

        buffer.add_request(request(id, length));//add a request to the buffer(calls add_request method)
        id++;//increments request counter

        int t = range(random);//wait time is generated
        std::cout << "Producer: me tired sleep for " << t << std::endl;//producer says how long it will sleep
        //and then it sleeps
        sleep(t);
    }
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void *slave(void *ptr)//slave thread code
{
    while (true)//slaves run forever
    {
        request r = buffer.process_request();//request is obtained with the process_request method

        if (r.id != -1)//if the request id !=-1 (means no requests)
        {
            std::cout << " Consumer " << pthread_self() << ": assigned request ID " << r.id
                      << ", processing request for the next:" << r.length << " seconds, current time is "
                      << clock() << std::endl;
                        //print what consumer id is, what request it is working on
                        //how long the request is, and what system time is

            sleep(r.length);//sleep for request length

            std::cout << " Consumer " << pthread_self() << ": completed request " << r.id << " at time" << clock() << std::endl;
            //print that the consumer is done with the request
        }
        else
        {
            std::cout << " Consumer " << pthread_self() << " no request to process"
                      << " at time" << clock() << std::endl;
                      //no requests found, something went wrong.  print it
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
    std::cin >> n_slaves;//queries and stores number of slave threads
    std::cout << "Enter the max time to produce a new request: ";
    std::cin >> *max;//queries and stores max wait time for request production
    std::cout << std::endl;
	
	buffer.set_bounds(n_slaves);//calls the set_bounds method to set the bounds

    pthread_t master_thread;
    std::vector<pthread_t> slave_threads(n_slaves); //instantiate master class

    pthread_create(&master_thread, NULL, master, (void *)max); //creates the master thread and executes it
    for (int i = 0; i < n_slaves; i++)                         //
        pthread_create(&slave_threads[i], NULL, slave, NULL);  //create n slave threads and execute them

    pthread_join(master_thread, NULL); // removes threads
    for (int i = 0; i < n_slaves; i++)
        pthread_join(slave_threads[i], NULL);
}
