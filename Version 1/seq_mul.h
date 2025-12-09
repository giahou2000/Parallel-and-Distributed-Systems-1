/*
 * Serial multiplication function
 */
 
//We will attempt to compute the multiplications that are not gonna be zero after the Hadamard product

CSC sequential_masked_triangle_counting(CSC A){
	/*
	cout<<endl;
	cout<<"Let's do the multiplication!!!"<<endl;
	cout<<endl;
	cout<<"Initialize variables"<<endl;
	cout<<endl;
	*/
	//the variables declaration and initialization if needed
	int i, j, nz1, nz2, column_index, size = 0, counter, dimension = A.row_ind.size() - 1;
	CSC final_matrix;
	final_matrix.row_ind.push_back(0);
	/*
	cout<<"Variables initialized"<<endl;
	cout<<endl;
	cout<<"Dimension is again "<<dimension<<endl;
	cout<<"Nonzero values are "<<A.col_ptr.size()<<endl;
	cout<<endl;
	*/
	//for each row
	for(i = 0 ; i < dimension ; i++){
		/*
		cout<<"@@@@@@@@@@@@@@"<<endl;
		cout<<endl;
		cout<<"For row: "<<i<<endl;
		cout<<endl;
		*/
		//Never ever EVER forget to reset the counter to zero again!!!
		counter = 0;
		
		
		/*
		 *for each nonzero element of the row do the multiplication process of row*col
		 */
		 
		 
		//how many nonzeros?
		nz1 = A.row_ind[i + 1] - A.row_ind[i];
		//cout<<"Nonzeros in this row: "<<nz1<<endl;
		//cout<<endl;
		//For each nonzero element build two vectors. The two vectors will contain the row and the column that will be multiplied. Then we will compute the multiplication and then save it.
		for(j = 0 ; j < nz1 ; j++){
			/*
			cout<<"********"<<endl;
			cout<<endl;
			cout<<"For the nonzero: "<<j<<endl;
			cout<<endl;
			
			cout<<"Build the row to be multiplied"<<endl;
			cout<<endl;
			*/
			//build the row with nonzero elements
			vector<int> row(A.col_ptr.begin() + A.row_ind[i], A.col_ptr.begin() + A.row_ind[i + 1]);
			
			//cout<<"Build the column to be multiplied"<<endl;
			//cout<<endl;
			//build the column with nonzero elements
			column_index = A.col_ptr[A.row_ind[i] + j];
			vector<int> col(A.col_ptr.begin() + A.row_ind[column_index], A.col_ptr.begin() + A.row_ind[column_index + 1]);
			
			//cout<<"Finally the actual multiplication"<<endl;
			//cout<<endl;
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
				counter++;
				/*
				cout<<"Value not zero. Let's store it to the final matrix."<<endl;
				cout<<endl;
				cout<<"Counter = "<<counter<<endl;
				cout<<endl;
				*/
				//save the value of the multiplication
				final_matrix.value.push_back(size);
				//cout<<"Value saved"<<endl;
				//cout<<endl;
				final_matrix.col_ptr.push_back(column_index);
				//cout<<"column_ptr saved"<<endl;
				//cout<<endl;
			}
		}
		//save the result
		final_matrix.row_ind.push_back(final_matrix.col_ptr.size());
		//cout<<"Row index saved"<<endl;
		//cout<<endl;
	}
	
	return final_matrix;
}






