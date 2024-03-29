/***************************************************************/
/*                                                             */
/* lizard.cpp                                                  */
/*                                                             */
/* To compile, you need all the files listed below             */
/*   lizard.cpp                                                */
/*                                                             */
/* Be sure to use the -lpthread option for the compile command */
/*   g++ -g -Wall -std=c++11 lizard.cpp -o lizard -pthread     */
/*                                                             */
/* Execute with the -d command-line option to enable debugging */
/* output.  For example,                                       */
/*   ./lizard -d                                               */
/*                                                             */
/***************************************************************/

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <thread>
#include <mutex>

#include "semaphore.hpp" // CL



using namespace std;

/*
 * This is a stub file.  It contains very little code and what
 * it does contain may need to be altered or removed.  It is
 * only provided for a starting point.
 *
 * The comments are probably useful.
 */


/*
 * Define "constant" values here
 */

/*
 * Make this 1 to check for lizards travelling in both directions
 * Leave it 0 to allow bidirectional travel
 */
#define UNIDIRECTIONAL       	0

/*
 * Set this to the number of seconds you want the lizard world to
 * be simulated.  
 * Try 30 for development and 120 for more thorough testing.
 */
#define WORLDEND             	30

/*
 * Number of lizard threads to create
 */
#define NUM_LIZARDS          	20

/*
 * Number of cat threads to create
 */
#define NUM_CATS             	2

/*	
 * Maximum lizards crossing at once before alerting cats
 */
#define MAX_LIZARD_CROSSING  	4

/*
 * Maximum seconds for a lizard to sleep
 */
#define MAX_LIZARD_SLEEP_TIME   3 // CL

/*
 * Maximum seconds for a cat to sleep
 */
#define MAX_CAT_SLEEP_TIME      3 // CL

/*
 * Maximum seconds for a lizard to eat
 */
#define MAX_LIZARD_EAT_TIME  	5 // CL

/*
 * Number of seconds it takes to cross the driveway
 */
#define CROSS_SECONDS        	2


/*
 * Declare global variables here
 */

Semaphore lizardSemaphore(MAX_LIZARD_CROSSING); // CL

int currentID;

/**************************************************/
/* Please leave these variables alone.  They are  */
/* used to check the proper functioning of your   */
/* program.  They should only be used in the code */
/* I have provided.                               */
/**************************************************/
int numCrossingSago2MonkeyGrass = 0; // CL
int numCrossingMonkeyGrass2Sago = 0; // CL
bool debug = false; // CL
bool running = true; // CL
/**************************************************/



/**
 * This class models a cat that sleep, wakes-up, checks on lizards in the driveway
 * and goes back to sleep. If the cat sees enough lizards it "plays" with them.
 */
class Cat {

	int       _id;        // the Id of the cat
	thread    _catThread; // the thread simulating the cat

	public:
		Cat (int id);
		int getId();
		void run();
		void wait();
		void sleepNow();
};


/**
  *
  * This simulates a cat that is sleeping and occasionally checking on
  * the driveway on lizards.
  *
  * @param theCat - the cat that is being run concurrently
  *
  * @return - N/A
  *
  * Status: Incomplete - Make changes as you see are necessary.
  */
void catThread ( Cat &theCat )
{

	if (debug)
    {
		cout << "[" << theCat.getId() << "] cat is alive\n";
		cout << flush;
    }

	while(running)
    {
		theCat.sleepNow();

		/*
	     * Check for too many lizards crossing
	     */
		if (numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago > MAX_LIZARD_CROSSING)
		{
		  cout << "\tThe cats are happy - they have toys.\n";
		  exit( -1 );
		}
    }
}



/**
 * Constructs a cat.
 *
 * @param id - the Id of the cat 
 */
Cat::Cat (int id)
{
	_id = id;
}

/**
 * Returns the Id of the cat.
 *
 * @return the Id of a cat
 */
int Cat::getId()
{
	return _id;
}


/**
 * Launches a cat thread.
 * 
 * Status: Incomplete - Make changes to this code.
 */
 void Cat::run()
 {
	 // launch the thread to simulate the cat's behavior

 }

 /**
  * Waits for a cat to finish running.
  *
  * Status: Incomplete - Make changes to this code.
  */
 void Cat::wait()
 {
	 // wait for the thread to terminate
 }


/**
 * Simulate a cat sleeping for a random amount of time
 *
 *
 * @return N/A
 *
 * Status: Completed - No need to change any of this code.
 */
void Cat::sleepNow()
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_CAT_SLEEP_TIME);

	if (debug)
    {
		cout << "[" << _id << "] cat sleeping for " << sleepSeconds << " seconds" << endl;
		cout << flush;
    }

	sleep( sleepSeconds );

	if (debug)
    {
		cout << "[" << _id << "] cat awake" << endl;
		cout << flush;
    }
}


class Lizard {
	int    _id;      // the Id of the lizard
	thread _aLizard; // the thread simulating the lizard

	public:
		Lizard(int id);
		int getId();
		void run();
		void wait();
		void sago2MonkeyGrassIsSafe();
		void crossSago2MonkeyGrass();
		void madeIt2MonkeyGrass();
		void eat();
		void monkeyGrass2SagoIsSafe();
		void crossMonkeyGrass2Sago();
		void madeIt2Sago();
		void sleepNow();

};

/**
  * Follows the algorithm provided in the assignment
  * description to simulate lizards crossing back and forth
  * between a sago palm and some monkey grass.
  *
  * @param aLizard - the lizard to be executed concurrently
  *
  * @return N/A

  * Status: Incomplete - Make changes as you see are necessary.
  */
void runThread( Lizard &aLizard )
{
	if (debug)
    {
      cout << "[" << aLizard.getId() << "] lizard is alive" << endl;
      cout << flush;
    }

	while(running)
    {
      /*
       * Follow the algorithm given in the assignment
       * using calls to the functions declared above.
       * You'll need to complete the implementation of
       * some functions by filling in the code.  Some
       * are already completed - see the comments.
       */

		/**** CL start ****/
		aLizard.sleepNow(); // lizard sleeps
		aLizard.sago2MonkeyGrassIsSafe(); // checks if safe to cross to monkey grass
		aLizard.crossSago2MonkeyGrass(); // crosses to monkey grass
		aLizard.madeIt2MonkeyGrass(); // signals that done
		aLizard.eat(); // eats and waits
		aLizard.monkeyGrass2SagoIsSafe(); //checks if it is safe to return home
		aLizard.crossMonkeyGrass2Sago(); //crosses the road
		aLizard.madeIt2Sago(); //waits at home
		/**** CL end ****/

    }

}


/**
 * Constructs a lizard.
 *
 * @param id - the Id of the lizard 
 */
Lizard::Lizard (int id)
{
	_id = id;
}

/**
 * Returns the Id of the lizard.
 *
 * @return the Id of a lizard
 */
int Lizard::getId()
{
	return _id;
}

/**
 * Launches a lizard thread.
 * 
 * Status: Incomplete - Make changes to this code.
 */
 void Lizard::run()
 {
	 // launch the thread to simulate the lizard's behavior
 }

 /**
  * Waits for a lizard to finish running.
  *
  * Status: Incomplete - Make changes to this code.
  */
 void Lizard::wait()
 {
	 // wait for the thread to terminate


 }






/**
 * Simulate a lizard sleeping for a random amount of time
 *
 * Status: Completed - No need to change any of this code.
 */
void Lizard::sleepNow()
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_SLEEP_TIME);

	if (debug)
    {
      cout << "[" << _id << "] sleeping for " << sleepSeconds << " seconds" << endl;
      cout << flush;
    }

	sleep( sleepSeconds );

	if (debug)
    {
      cout << "[" << _id << "] awake" << endl;
      cout << flush;
    }
}




/**
 *
 * Returns when it is safe for this lizard to cross from the sago
 * to the monkey grass.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::sago2MonkeyGrassIsSafe()
{
	if (debug)
    {
		cout << "[" << _id << "] checking  sago -> monkey grass" << endl;
		cout << flush;
    }

	lizardSemaphore.wait(); // CL

	if (debug)
    {
		cout << "[" << _id << "] thinks  sago -> monkey grass  is safe" << endl;
		cout << flush;
    }
}


/**
 *
 * Delays for 1 second to simulate crossing from the sago to
 * the monkey grass. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossSago2MonkeyGrass()
{
	if (debug)
    {
      cout << "[" << _id << "] crossing  sago -> monkey grass" << endl;
      cout << flush;
    }

	/*
	 * One more crossing this way
	 */
	numCrossingSago2MonkeyGrass++;

	/*
     * Check for lizards cross both ways
     */
	if (numCrossingMonkeyGrass2Sago && UNIDIRECTIONAL)
    {
		cout << "\tCrash!  We have a pile-up on the concrete." << endl;
		cout << "\t" << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t" << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
    }


	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

    /*
     * That one seems to have made it
     */
    numCrossingSago2MonkeyGrass--;
}


/**
 * Tells others they can go now
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2MonkeyGrass()
{
	/*
     * Whew, made it across
     */
	if (debug)
    {
		cout << "[" << _id << "] made the  sago -> monkey grass  crossing" << endl;
		cout << flush;
    }


	lizardSemaphore.signal(); // CL


}


/**
 * Simulate a lizard eating for a random amount of time
 *
 * Status: Completed - No need to change any of this code.
 */
void Lizard::eat()
{
	int eatSeconds;

	eatSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_EAT_TIME);

	if (debug)
    {
		cout << "[" << _id << "] eating for " << eatSeconds << " seconds" << endl;
		cout << flush;
    }

	/*
     * Simulate eating by blocking for a few seconds
     */
	sleep( eatSeconds );

	if (debug)
    {
      cout << "[" << _id << "] finished eating" << endl;
      cout << flush;
    }
}


/**
 * Returns when it is safe for this lizard to cross from the monkey
 * grass to the sago.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::monkeyGrass2SagoIsSafe()
{
	if (debug)
    {
		cout << "[" << _id << "] checking  monkey grass -> sago" << endl;
		cout << flush;
    }

	lizardSemaphore.wait();

	if (debug)
    {
		cout << "[" << _id << "] thinks  monkey grass -> sago  is safe" << endl;
		cout << flush;
    }
}



/**
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossMonkeyGrass2Sago()
{
	if (debug)
    {
		cout << "[" << _id << "] crossing  monkey grass -> sago" << endl;
		cout << flush;
    }

    /*
     * One more crossing this way
     */
	numCrossingMonkeyGrass2Sago++;


    /*
     * Check for lizards cross both ways
     */
	if (numCrossingSago2MonkeyGrass && UNIDIRECTIONAL)
    {
		cout << "\tOh No!, the lizards have cats all over them." << endl;
		cout << "\t " << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t " << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
    }

	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

	/*
     * That one seems to have made it
     */
	numCrossingMonkeyGrass2Sago--;
}


/**
 *
 * Tells others they can go now
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2Sago()
{
	/*
     * Whew, made it across
     */
	if (debug)
    {
		cout << "[" << _id << "] made the  monkey grass -> sago  crossing" << endl;
		cout << flush;
    }

	lizardSemaphore.signal();
}





/*
 * main()
 *
 * Should initialize variables, locks, semaphores, etc.
 * Should start the cat thread and the lizard threads
 * Should block until all threads have terminated
 * Status: Incomplete - Make changes to this code.
 */
int main(int argc, char **argv)
{
	/*
	 * Declare local variables
     */
	/**** CL start ****/
	std::thread allThreads[NUM_LIZARDS + NUM_CATS];
	/**** CL end ****/

	/*
     * Check for the debugging flag (-d)
     */
	debug = false; // CL
	if (argc > 1)
		if (strncmp(argv[1], "-d", 2) == 0)
			debug = 1;


	/*
     * Initialize variables
     */
	numCrossingSago2MonkeyGrass = 0;
	numCrossingMonkeyGrass2Sago = 0;
	running = true; // CL


	/*
     * Initialize random number generator
	 */
	srandom( (unsigned int)time(NULL) );


	/*
     * Initialize locks and/or semaphores
     */




	/*
     * Create NUM_LIZARDS lizard threads
     */
	Lizard** allLizards = new Lizard*[NUM_LIZARDS];

	/**** CL start ****/
	for(int i = 0; i < NUM_LIZARDS; i++)
	{
		allLizards[i] = new Lizard(i);
	}
	/**** CL end ****/

    /*
     * Create NUM_CATS cat threads
     */

	/**** CL start ****/
	Cat** allCats = new Cat*[NUM_CATS];

	for(int i = 0; i < NUM_CATS; i++)
	{
		allCats[i] = new Cat(i);
	}
	/**** CL end ****/

	/*
	 * Run NUM_LIZARDS and NUM_CATS threads
	 */

	/**** CL start ****/
	// Runs threads for Lizards
	for(int i = 0; i < NUM_LIZARDS; i++)
	{
		allThreads[i](runThread, allLizards[i]); //error
	}

	// Runs threads for Cats
	for(int i = 0; i < NUM_CATS; i++)
	{
		allThreads[i + NUM_LIZARDS](catThread, allCats[i]); //error
	}
	/**** CL end ****/

	/*
     * Now let the world run for a while
     */
	sleep( WORLDEND );


	/*
     * That's it - the end of the world
     */
	running = false; // CL


    /*
     * Wait until all threads terminate
     */

	/**** CL start ****/
	//Terminates all threads and joins main thread
	for(int i = 0; i < NUM_LIZARDS; i++)
	{
		allThreads[i].join();
	}
	/**** CL end ****/






	/*
     * Delete the locks and semaphores
     */



	/*
	 * Delete all cat and lizard objects
	 */
	/**** CL start ****/
	for(int i = 0; i < NUM_LIZARDS; i++)
	{
		delete allLizards[i];
	}

	for(int i = 0; i < NUM_CATS; i++)
	{
		delete allCats[i];
	}
	delete allCats;
	/**** CL end ****/
	delete allLizards;



	/*
     * Exit happily
     */
	return 0;
}






