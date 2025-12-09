//Parallel and distributed systems | Project 1 | main file for running and measuring time
#define NUM_THREADS	12
#include <chrono>
#include "coo_2_csc.h"
//for sequential
#include "seq_mul.h"
//for cilk
//#include "cilk_mul.h"
//for openmp
//#include "mp_mul.h"

//for pthread
//#include "pthreaded_mul.h"



using namespace std::chrono;

int main(int argc, char* argv[])
{
	cout << "Let's begin" << endl;
	cout << endl;
	
	cout << "MTX File: " << argv[1] << endl;
	cout << endl;
	
	//read the mtx file and build the csc format
	
	CSC A = coo_2_csc(argv[1]);
	
	cout << "The matrix is at csc form now" << endl;
	
	ofstream myfile;
	myfile.open ("pt_12_yt.dat");
	//omp_set_dynamic(0);
	//omp_set_num_threads(12);
	//for(int i = 0 ; i < 20 ; i++){
	
	//Start timer
	auto start = high_resolution_clock::now();
	
	//for sequential
	//CSC C = sequential_masked_triangle_counting(A);
	
	//for cilk
	//vector<int> C = masked_triangle_counting_cilk(A);
	
	//for openmp
	//vector<int> C = mp_masked_triangle_counting(A);
	
	//for pthreads
	/*create the threads
	pthread_t threads[NUM_THREADS];
	int t;

	//how many blocks will a thread process
	//A.row_ind.size() == dimension of the matrix
	int blocks = (A.row_ind.size() - 1) / NUM_THREADS;
	
	//create the input structs
	vector<int> results(A.col_ptr.size());
	input in[NUM_THREADS];
	int rc;
	
	//Start timer
	auto start = high_resolution_clock::now();
	
	//for each thread except the last one calculate a specific part of the multiplication
	for(t = 0; t < NUM_THREADS - 1; t++) {
		in[t].C = &results;
		in[t].row_start = 0 + t * blocks;
		in[t].row_end = (t+1) * blocks;
		in[t].Apt = A;
        rc = pthread_create(&threads[t], NULL, pt_masked_triangle_counting,(void*) &in[t]);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
    }
	
	//for the last thread(so it will calculate everything that has left) using the modulo calculation
	in[NUM_THREADS - 1].row_start = 0 + (NUM_THREADS - 1) * blocks;
	in[NUM_THREADS - 1].row_end = NUM_THREADS * blocks + (A.row_ind.size() % NUM_THREADS);
	in[NUM_THREADS - 1].C = &results;
	in[NUM_THREADS - 1].Apt = A;
    rc = pthread_create(&threads[NUM_THREADS - 1], NULL, pt_masked_triangle_counting, (void*) &in[NUM_THREADS - 1]);
	if (rc){
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
    }

    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
	*/
	
	//stop timer
	auto stop = high_resolution_clock::now();
	
	
	
	//get the duration
	auto duration = duration_cast<microseconds>(stop - start);
	
	cout << "Duration of the multiplication is: " << duration.count() << "microseconds" << endl;


	
	myfile << duration.count() << endl;;
	//}
	myfile.close();
	//cout<<endl;
	//pthread_exit(NULL);
	
	
	
	int tr_num = 0;
	//Count the number of triangles for sequential
	for(int d:C.value){
		tr_num = tr_num + d;
	}
	
	//the number we have to count is
	c = tr_num/2;
	
	cout << "The number of triangles is: " << c <<endl;
	
	/*Count the number of triangles for cilk/openmp
	for(int d:c){
		tr_num = tr_num + d;
	}
	
	c_parallel = tr_num/2;
	cout << "The number of triangles is: " << c_parallel <<endl;
	*/
	
	/*Count the number of triangles for pthreads(if pthreads work properly)
	for(int d:results){
		tr_num = tr_num + d;
	}
	c_parallel = tr_num/2;
	cout << "The number of triangles is: " << c_parallel <<endl;
	*/
	
	
	return 0;
}