/*
 * Pthreaded multiplication function
 *God of speed
 */
#include <pthread.h>
//We will attempt to compute the multiplications that are not gonna be zero after the Hadamard product using pthreads(Wish us good luck!!!)

struct input {
	CSC Apt;
	int row_start;
	int row_end;
	vector<int>* C;
};

void* pt_masked_triangle_counting(void* in){
	//the variables declaration and initialization if needed
	struct input* info = (struct input*) in;
	
	int dimension = info->Apt.row_ind.size() - 1;
	//for each row
	for(int i = 0 + info->row_start ; i < info->row_end ; i++){
		//cout<<"i is "<<i<<endl;
		/*
		 *for each nonzero element of the row do the multiplication process of row*col
		 */
		 int size = 0;
		 int column_index;
		//For each nonzero element build two vectors. The two vectors will contain the row and the column that will be multiplied. Then we will compute the multiplication and then save it.
		for(int j = (info->Apt.row_ind[i]) ; j < (info->Apt.col_ptr[i + 1]) ; j++){
			//cout<<"j is "<<j<<endl;
			//build the row with nonzero elements
			vector<int> row(info->Apt.col_ptr.begin() + info->Apt.row_ind[i], info->Apt.col_ptr.begin() + info->Apt.row_ind[i + 1]);
			//build the column with nonzero elements
			column_index = (info->Apt.col_ptr[j]);
			//cout<<"column_index is "<<column_index<<endl;
			vector<int> col((info->Apt.col_ptr.begin()) + (info->Apt.row_ind[column_index]), (info->Apt.col_ptr.begin()) + (info->Apt.row_ind[column_index + 1]));
			

			//get the result of the multiplication
			vector<int> inters_val;
			std::set_intersection(row.begin(), row.end(), col.begin(), col.end(), std::back_inserter(inters_val));
			//cout<<"Multiplication is over."<<endl;
			//cout<<endl;
			
			
			//calculate the result of the multiplication
			size = inters_val.size();
			//cout<<"size is "<<size<<" ";
			//cout<<endl;
	
			//cout<<"Multiplication result is: "<<size<<endl;
			//cout<<endl;
			//save the result
			if(size > 0){
				info->C->at(j) = size;
			}
		}
	}
}
