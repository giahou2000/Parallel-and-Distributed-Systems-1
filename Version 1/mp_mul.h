/*
 * OpenMP multiplication function
 *The speedmaster
 */
 
#include <omp.h>
 
//We will attempt to compute the multiplications that are not gonna be zero after the Hadamard product using the OpenMP (Wish us good luck again and again!!!)

vector<int> mp_masked_triangle_counting(CSC A){

	//the variables declaration and initialization if needed
	int dimension = A.row_ind.size() - 1;
	//CSC final_matrix;
	//final_matrix.row_ind.push_back(0);
	vector<int> C(A.col_ptr.size());
	
	//for each row
	#pragma omp parallel
	for(int i = 0 ; i < dimension ; i++){
		/*
		 *for each nonzero element of the row do the multiplication process of row*col
		 */
		 int size = 0;
		 int column_index;
		//For each nonzero element build two vectors. The two vectors will contain the row and the column that will be multiplied. Then we will compute the multiplication and then save it.
		#pragma omp for nowait
		for(int j = A.row_ind[i] ; j < A.col_ptr[i + 1] ; j++){
			
			//build the row with nonzero elements
			vector<int> row(A.col_ptr.begin() + A.row_ind[i], A.col_ptr.begin() + A.row_ind[i + 1]);
			
			//build the column with nonzero elements
			column_index = A.col_ptr[j];
			vector<int> col(A.col_ptr.begin() + A.row_ind[column_index], A.col_ptr.begin() + A.row_ind[column_index + 1]);
			

			//get the result of the multiplication
			vector<int> inters_val;
			std::set_intersection(row.begin(), row.end(), col.begin(), col.end(), std::back_inserter(inters_val));
			//cout<<"Multiplication is over."<<endl;
			//cout<<endl;
			
			
			//calculate the result of the multiplication
			size = inters_val.size();
			//cout<<"Multiplication result is: "<<size<<endl;
			//cout<<endl;
			//save the result
			if(size > 0){
				C.at(j) = size;
			}
		}
	}
	
	return C;
}