#include "util/util.hpp";

int util_generateid() {
	const int ID_SIZE = 5;;
	srand(time(0));

	int id;
	int id_nums[ID_SIZE];

	id = 0;
    for (int i = 0; i < ID_SIZE; i++) {
    	id_nums[i] = rand()%10 + 1;
    }
    for (int i = 0; i < ID_SIZE; i++) {
    	id = id + (id_nums[i] * pow(10, i));
    }
	return id;
}