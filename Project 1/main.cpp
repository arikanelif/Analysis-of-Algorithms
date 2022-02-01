//Elif ARIKAN
//150180010

#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include <time.h> // for calculate the time

using namespace std;

struct set{ // tweet_id	tweet_datetime	tweet_unixtime	artist_name	track_title	country
    string tweet_id; // Enumeration of the Tweet 
    string tweet_datetime ;//Tweet time in a structured format 
    string tweet_unixtime; // Tweet time in Unix format 
    string artist_name; // Artist name of the song
    string track_title; //Name of the song
    string country; //Tweet location
};

vector<struct set> my_set;

string convert(string str) {  // to convert string case insensitive 
    transform(str.begin(), str.end(), str.begin(), ::tolower); // call the transform function into the library. 
    return str;  // return the string which convert case insensitive.
}

void write_to_file(int N, string outputfile){ // writes all the data to the file ,N is the number of data, 
    ofstream myfile(outputfile);  // opens the file
    
    if (!myfile){ // checks whether the file has been opened
        cerr << "File cannot be opened!" <<endl;
        exit(1);
        }
    
    myfile <<"tweet_id	tweet_datetime	tweet_unixtime	artist_name	track_title	country\n"; // writes the header line
    for(int i=0; i < N; i++){ // writes all lines one by one
        myfile << my_set[i].tweet_id << "\t";
        myfile << my_set[i].tweet_datetime << "\t";
        myfile << my_set[i].tweet_unixtime<< "\t";
        myfile << my_set[i].artist_name << "\t";
        myfile << my_set[i].track_title << "\t";
        myfile << my_set[i].country;
        myfile << "\n"; 

    }
    
    myfile.close(); // closes the file
}

// tweet_id	tweet_datetime	tweet_unixtime	artist_name	track_title	country
void read_to_file(int N, string inputfile)
{
    ifstream file(inputfile);  // opens the file to read.
	if (!file){ // checks whether the file has been opened.
		cerr << "File cannot be opened!";  //error message 
		exit(1);
	}
    string line;
	getline(file, line); //this is the header line
	for(int i = 0; i<N; i++){ // read from file and assign data to my_settor
        struct set new_set;
        
		getline(file, line, '\t'); //tweet id(string)
        new_set.tweet_id = line;
        
        getline(file, line, '\t'); //datatime (string)
        new_set.tweet_datetime = line;

		getline(file, line, '\t'); //unixtime (string)
        new_set.tweet_unixtime = line;
        
        getline(file, line, '\t'); //artist name (string)
        new_set.artist_name = line;

		getline(file, line, '\t'); //track title(string)
        new_set.track_title = line;

        getline(file, line); //country (string)
        new_set.country = line;

        my_set.push_back(new_set); // push set into vector
	}

}



int partition(int p, int r) // p is low index of my_set vector , r is the high index .
{  
    struct set pivot= my_set[r]; // last element is choose as pivot
    int i=p-1; // Index of smaller element and indicates the 
                // right position of pivot found so far
    for(int j=p; j<r;j++) // initial of j is low index (p) and j increas one by one until r (high index) 
    {                     // to find smaller and bigger element than our country_key 
        if( convert(my_set[j].country) <= convert( pivot.country ))// if current element'country name is smaller than 
        {                                                          //(or equal) pivot country name as ascending order
            if (convert(my_set[j].country)  == convert(pivot.country) ) //if country names are equal, then we check artist name
            {
                
                if( convert(my_set[j].artist_name) <= convert(pivot.artist_name)) // if current element's artist name is smaller than
                {                                                                 //(or equal) pivot's artist name as ascending order
                    if(convert(my_set[j].artist_name) == convert(pivot.artist_name)) //if country names and artist name are equal,
                                                                                    // then we check tweet unixtime
                    {
                        if(my_set[j].tweet_unixtime < pivot.tweet_unixtime)   // if current element's unixtime smaller than pivot's
                        {                                                      
                            i++;        // increremnt the smaller position
                            swap(my_set[i], my_set[j]);                 //we swap current element with index of smaller element i.
                        }
                    }
                    else 
                    {
                        i++;
                        swap(my_set[i], my_set[j]);
                    }
                }
                
            }
            else 
            {
                i++;
                swap(my_set[i], my_set[j]);
            }

        }
    }
    swap(my_set[i + 1], my_set[r]);
    return (i+1);
}
int ran_partition(int p,int r)
{ // Generates Random Pivot, swaps pivot with
// end element and calls the partition function
    srand(time(NULL));
    int random = p + rand() % (r - p);
 
    // Swap A[random] with A[high]
    swap(my_set[random], my_set[r]);
 
    return partition(p,r);
}

//p --> Starting index,
//r --> Ending index 
void quickSort(string A, int p,int r){
    if(p<r)
    {
        int q;
        if (A=="deterministic")
            q= partition(p,r);
        else if(A=="randomized")
            q=ran_partition(p,r);
        quickSort(A, p,(q-1));
        quickSort(A, (q+1),r);
    }
}

int main(int argc, char *argv[]){

    long int N = stoi(argv[1]); // number of the tweets to be sorted .
    string A = (argv[2]); //name of the pivot selection algorithm (either randomized or deterministic)
    string I =argv[3] ; //input file path (e.g., unsorted.csv)
    string O = argv[4]; //output file path for saving the result (e.g., output.csv)

    read_to_file(N,I);
    
    clock_t t; // to calculate the time of running
    t = clock(); // start time
    quickSort(A, 0,N-1);
    t = clock() - t; // finish time
    cout << "Sorted in " << (((float)t)/CLOCKS_PER_SEC)*1000 <<" miliseconds by using "<< A <<" pivot selection."<< endl;  // *1000 for convert second to milisecond.
    write_to_file(N, O) ;  // writes the sorting data to the file. 
    
	return 0;
}