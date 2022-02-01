//Elif ARIKAN
//150180010

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include <vector>
#include <time.h> // for calculate the time

using namespace std;

class vehicles{ // class vehicles keep the vehicles which in vehicles.txt.
public:
    int vehicle_ID;
    string location;
    double distance;
    int speed;
    double time() {
        return (distance/speed);
    }
};

class requests{ // class request keep the N request in request.txt
public:
    string location;
    double distance;
    int lucky_number;
};

vector<class requests> all_requests;

class MinHeap{
    int capacity;
    int heap_size;
    vector <class vehicles> all_vehicles; 
public:
    MinHeap();
    int parent(int i) { return (i-1)/2; }// to get inde of parent of node at index i
    int left(int i) { return (2*i + 1); } // to get index of left child of node at index i
    int right(int i) { return (2*i + 2); } // to get index of right child of node at index i
    void min_heapify(int);
    void build_min_priority_heap();
    vehicles extract();
    void decrease_key(int);
    void insert (vehicles);
    void read_vehicles();
    vehicles update(vehicles, int);
};
MinHeap ::MinHeap(){
    heap_size=0;
    capacity=1642; // number is given at hw pdf. total number of cars is 1642.
}
void MinHeap::read_vehicles()
{
    ifstream file("vehicles.txt");  // opens the file to read.
	if (!file){ // checks whether the file has been opened.
		cerr << "File cannot be opened!";  //error message 
		exit(1);
	}
    string line;
    int x;
    double y;
	getline(file, line); //this reads the header line
	while(getline (file,line , '\t')){ // read from file all vehicles 
        class vehicles new_vehicles;
        stringstream ss(line); // convert string to integer 
        ss >> x;
        new_vehicles.vehicle_ID =x;
        
        getline(file, line, '\t'); 
        new_vehicles.location= line;

		getline(file, line, '\t');
        stringstream sss(line); // convert string to double
        sss>>y;
        new_vehicles.distance = y;

        getline(file, line);
        stringstream geek1(line); // convert string to integer 
        geek1 >> x;
        new_vehicles.speed =x;
    
        all_vehicles.push_back(new_vehicles); // push class into vector
        heap_size++;
	}
}

void read_requests(int N)
{
    ifstream file("requests.txt");  // opens the file to read.
	if (!file){ // checks whether the file has been opened.
		cerr << "File cannot be opened!";  //error message 
		exit(1);
	}
    string line;
    int x;
    double y;
	getline(file, line); //this reads the header line
	for(int i = 0; i<N; i++){ // read from file and assign data to 
        class requests new_requests;
        
        getline(file, line, '\t');
        new_requests.location= line;

		getline(file, line, '\t');
        stringstream sss(line); // convert string to double
        sss>>y;
        new_requests.distance = y;

        getline(file, line); 
        stringstream ssss(line); // convert string to integer
        ssss >> x;
        new_requests.lucky_number =x;
    
        all_requests.push_back(new_requests); // push class into vector
	}

}

void MinHeap::min_heapify(int i)  // heapify given index i to replace it at rigth place.
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && all_vehicles[l].time() < all_vehicles[i].time())
        smallest = l;
    if (r < heap_size && all_vehicles[r].time() < all_vehicles[smallest].time() )
        smallest = r;
    if (smallest != i)
    {
        swap(all_vehicles[i], all_vehicles[smallest]);
        min_heapify(smallest);
    }
}
void MinHeap::build_min_priority_heap()
{
    for (int i = (heap_size/ 2 - 1); i >= 0; i--)
        min_heapify(i);
}

vehicles MinHeap::extract() {
    vehicles min_time = all_vehicles[0]; // first vehicles(node) of heap is correspond to a template.
    all_vehicles[0] = all_vehicles[heap_size-1]; // last element is correspond to first element to decreasing heapsize
    heap_size--;
    min_heapify(0); // first element is heapifying to replace correct place.
    return min_time;   // return our template which is include first element of heap.
}

void MinHeap::decrease_key(int i)
{
    all_vehicles[i].distance= 0;  // time of key value is decreased by resetting decreasing.
    while (i != 0 && all_vehicles[parent(i)].time() > all_vehicles[i].time())
    {
       swap(all_vehicles[i], all_vehicles[parent(i)]);
       i = parent(i);
    }
}

void MinHeap::insert(vehicles new_v)
{
    heap_size++; // first heap_size increased
    int i = heap_size - 1; // to reach the last element (-1) 
    all_vehicles[i] = new_v; // insert the new key at the end
    while (i != 0 && all_vehicles[parent(i)].time() > all_vehicles[i].time()) // compare last elements time with its parent time ,then swap
    {
       swap(all_vehicles[i], all_vehicles[parent(i)]); 
       i = parent(i);
    }
}
vehicles MinHeap:: update( vehicles e_veh ,int i) //distance and location are updated 
{
    e_veh.distance=all_requests[i].distance; 
    e_veh.location=all_requests[i].location;
    return e_veh;
}

int main(int argc, char *argv[]){
    long int N = stoi(argv[1]); //numbers of requests.
    //task 1
    MinHeap minheap;
    read_requests(N);
    minheap.read_vehicles();
    minheap.build_min_priority_heap();

    ofstream myfile("call_history.txt");  // opens the output file
    if (!myfile){ // checks whether the file has been opened
        cerr << "File cannot be opened!" <<endl;
        exit(1);
    }
    clock_t t; // to calculate the time of running
    t = clock(); // start time
    int i=0; // to count request
    int j=0; // number of operation
    while(j<N) // compare j and N based on operation number.
    {   
        //task 2
        vehicles extracted; 
        if(all_requests[i].lucky_number == 0) //if lucky number is equal to
        {
            extracted =minheap.extract(); //extract the vehicles that has minimum time.
            j++; // opearation number is increased after extract. 
            myfile << extracted.vehicle_ID << endl; // vehicle id which is extracted from heap is writed into output file.
        } 
        else  // if lucky_number not equal to 0
        {
            minheap.decrease_key(all_requests[i].lucky_number);
            j++; // opearation number is increased after decrease.
            extracted = minheap.extract();
            j++; // opearation number is increased after extract.
            myfile << extracted.vehicle_ID << endl;
        }
        //task 3
        extracted= minheap.update(extracted,i);  //  update location and destination vehicles which is extacted from the heap.
        minheap.insert(extracted); // updated vehicle is added back into the heap.
        j++; // opearation number is increased after insert.
        i++; // increase to call new request
    }
    t = clock() - t; // finish time
    
    myfile.close(); // closes the output file
    
    cout << ((float)t)/CLOCKS_PER_SEC << endl; 


    
	return 0;
}