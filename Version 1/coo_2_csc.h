/*
 *Import the .mtx, convert to symmetric and then to csc
 */
 
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;


struct CSC {
	std::vector<int> row_ind;
	std::vector<int> col_ptr;
	std::vector<int> value;
};

//the important function that saves our lives X))
CSC coo_2_csc(std::string coo_mat_name) {
	/*
	 *important parameters and initialization of them
	*/
	int dimension = 0;
	int m = 0;
	int x, y, i, j;
	std::vector<int> csc_row;
	std::vector<int> csc_col;
	csc_row.push_back(0);
	std::string line;
	std::string X_coo;
	std::string Y_coo;
	std::string dim;
	//A helper vector to build the symmetric matrix from the lower triangular coo format
	//cout<<"Building the helper vector"<<endl;
	vector<vector<int>> helper;
	
	/*
	 *get the given file
	*/
	ifstream file(coo_mat_name);
	
	//if no matrix is given in command line...(just to be sure)
	if (!file){
		cout<<"Please give me a file"<<endl;
		CSC Error;
		return Error;
	}
	/*
	 *extract the matrix's dimension and data
	*/
	while(getline (file, line)){
		
		//we need to get rid of the comments and description of the file
		char unwanted[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','p','r','s','t','y','u','w','z','%','-'};
		if(line.find_first_of(unwanted) != -1){
			continue;
		} else if(m == 0) {
			//read the dimension of the matrix
			std::istringstream stream(line);
			stream>>dim;
			dimension = atoi(dim.c_str());
			cout<<"The matrix's dimension is:"<<dimension<<endl;;
			m = 1;
			helper.resize(dimension);
		} else{
			//Now it's time to read the coordinates
			std::istringstream stream(line);
			stream>>Y_coo>>X_coo;
			x = atoi(X_coo.c_str()) -1;
			y = atoi(Y_coo.c_str()) -1;
			
			//checking the coo coordinates
			//cout<<y<<" "<<x<<endl;
			
			//storing coordinates
			if(x!=-1 || y!=-1){
				//cout<<"Storing:"<<endl;
				helper[y].push_back(x);
				//And beacause the matrix is symmetric...
				helper[x].push_back(y);
				//cout<<"Values stored"<<endl;
			}
		}
		//if we have read the whole file(that's unnecessary)
		if(x==-1 || y==-1){
			cout<<"END OF FILE READING"<<endl;
			break;
		}
	}
	//cout<<"End of while"<<endl;
	
	
	/*
	 *csc building
	 */
	 
	cout<<"Start building csc"<<endl;
	for(i = 0 ; i < dimension ; i++){
		int size = helper[i].size();
		if(size > 0){
			csc_row.push_back(size + csc_row[i]);
			for (j = 0 ; j < size ; j++){
				csc_col.push_back(helper[i][j]);
			}
		}else{
			csc_row.push_back(csc_row[i]);
			}
	}
	cout<<"CSC completed"<<endl;
	
	//build a CSC struct with the csc matrix to return it
	cout<<"Storing the csc to return it"<<endl;
	CSC csc_mat;
	csc_mat.row_ind = csc_row;
	csc_mat.col_ptr = csc_col;
	return csc_mat;
}