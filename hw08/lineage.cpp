/* lineage.cpp
 *
 * Author: Zachary Meyers
 * Date: 4/1/23
 *
 * Purpose: Support additional mutation commands
 * using recursive functions  
 *
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
struct Gene;

struct Mutation {
    int cost;
    Gene *target;
};

struct Gene {
    string sq; // Name of gene sequence
    bool seen; // Used in recursive functions to avoid loops
    Mutation mut;
    int mut_count;
};

const string EVOLVE = "e";
const string E_STEPS = "es";
const string ENE_EVOLVE = "ene";
const string PATH = "path";
const string QUIT = "q";

Gene *read_genes(string filename, int *num_genes);
void populate_nodes(Gene *genes, ifstream *inf, int num_nodes);
void populate_links(Gene *genes, ifstream *inf, int num_nodes);
int index_of(Gene *genes, string seq, int num_nodes);
void init(Gene *genes, int num_nodes);
void prompt_and_execute(Gene *genes, int num_genes);
Gene *index_helper(Gene *genes, int num_genes, string gene);
void clear_seen(Gene *genes, int num_genes);
void print_query(Gene *genes, int num_genes);
bool can_evolve(Gene *genes, int num_genes, Gene *src, string tgt);
int evolution_steps(Gene *genes, int num_genes, Gene *src, string tgt
,int *steps);
bool energetic_evolution(Gene *genes, int num_genes, Gene *src, 
string tgt, int allowed_energy, int *used_energy);
bool evo_path(Gene *genes, int num_genes, Gene *src, 
string tgt, int *counter, string *gene_path);
void evo_path_helper(string *gene_path, int counter, int *iteration);


int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: No filename provided as an argument" << endl;
        exit(EXIT_FAILURE);
    }

    //After these two lines execute, all_genes is a pointer to the array of 
    //gene information read in from a given data file, and num_genes contains
    //number of genes stored in that array.
    int num_genes;
    Gene *all_genes = read_genes(argv[1], &num_genes);

    //USE all_genes AND num_genes AFTER THIS LINE TO CONTINUE THE COMPUTATION

    //Call prompt_and_execute() to take user input
    prompt_and_execute(all_genes, num_genes);

    //Clear memory
    delete [] all_genes;
    return 0;

}

// read_genes
// Input: A file name and a pointer to store the number of genes in the file.
// Description: Read in a file provided the user and use the data to populate
//              an array of Genes.
// Output: Returns a pointer to an array of Genes (populated with the contents
//         of a data file), and indirectly returns the number of array elements
//         through the num_genes pointer.
Gene *read_genes(string filename, int *num_genes)
{
    ifstream inf;
    inf.open(filename);
    if (inf.fail()) {
        cout << "ERROR OPENING FILE: Exiting Program" << endl;
        exit(EXIT_FAILURE);
    }

    inf >> *num_genes;

    // Create and populate the the names in the array of genes
    Gene *dna_p = new Gene[*num_genes];
    init(dna_p, *num_genes);
    populate_nodes(dna_p, &inf, *num_genes);

    // Reset the file to read in the mutation information
    inf.close();
    inf.open(filename);
    inf >> *num_genes; // NEED TO READ "past" NUMBER ON FIRST LINE

    populate_links(dna_p, &inf, *num_genes);

    inf.close();

    return dna_p;
}

// init
// Input: A pointer to an uninitialized array of genes and the size of
//        that array.
// Description: Initializes the array of genes with non-garbage information.
// Output: Initializes the array pointed to by 'dna'.
void init(Gene *dna, int num_nodes)
{
    for (int i = 0; i < num_nodes; i++) {
        dna[i].sq = "";
        dna[i].seen = false;
        dna[i].mut.cost = -1;
        dna[i].mut.target = nullptr;
    }
}

// populate_nodes
// Input: A pointer to an array of genes, a pointer to a file stream,
//        and the size of the array.
// Description: Read the file pointed to and set the sequence name of
//              each gene in the array.
// Output: Populates the sequence information for the gene array pointed to by
//         'dna'. Moves the file pointer further into the file.
void populate_nodes(Gene *dna, ifstream *inf, int num_nodes)
{
    string seq, mut_seq;
    int num_muts, num;
    for (int i = 0; i < num_nodes; i++) {
        *inf >> seq >> num_muts;
        dna[i].sq = seq;
        dna[i].mut_count = num_muts;
        for (int j = 0; j < num_muts; j++) {
            *inf >> mut_seq >> num;
        }
    }
}

// populate_links
// Input: A pointer to an array of genes, a pointer to a file stream,
//        and the size of the array.
// Description: Read the file pointed to and populate the mutation
//              information between genes in the array. We assume the data file
//              only contains well-formed input.
// Output: Populates the mutation information for the gene array pointed to by
//         'dna'. Moves the file stream pointed to further into the file.
void populate_links(Gene *dna, ifstream *inf, int num_nodes)
{
    string seq, mut_seq;
    int num_muts;
    for (int i = 0; i < num_nodes; i++) {
        *inf >> seq >> num_muts;

        // Add the one mutation if it exists
        if (num_muts == 1) {
            int cost;
            *inf >> mut_seq >> cost;

            int index = index_of(dna, mut_seq, num_nodes);

            dna[i].mut.cost = cost;
            dna[i].mut.target = &dna[index];
        }
    }
}

// index_of
// Input: An array of genes, a gene sequence, and the size of the array.
// Description: Find the index of the given sequence in the array.
// Output: The index of the sequence in the array, or -1 if the sequence is not
//         in the array.
int index_of(Gene *dna, string seq, int num_nodes)
{
    for (int i = 0; i < num_nodes; i++) {
        if (dna[i].sq == seq) {
            return i;
        }
    }
    return -1;
}

  /* prompt_and_execute
   * Input: An array of Gene structs and total
   * number of genes
   * Description: Repeatedly prompt user for a query
   * and execute the requested function
   * Output: None (void)
   */
void prompt_and_execute(Gene *genes, int num_genes)
{
    //Create variables to store user input
    string query, source_gene, target_gene;
    int cost;
    //Prompt user for input
    cout << "Enter a query: ";
    cin >> query;
    //While quit command is not entered
    while(query != QUIT){
        clear_seen(genes, num_genes);
        //Print query
        if(query == "p"){
        print_query(genes, num_genes);}
        //Can_evolve query
        else if(query == EVOLVE){
            //Define variables to handle additional input
            cin >> source_gene >> target_gene;
            //If can_evolve() return true, print out a success statement
            if(can_evolve(genes, num_genes, 
            index_helper(genes, num_genes, source_gene), target_gene))
            {
                cout << source_gene << " can evolve into " << target_gene;
                cout << endl;
            }
            //Otherwise, print out it isn't possible
            else
            {
                cout << source_gene << " cannot evolve into " << target_gene;
                cout << endl;
            }
        }
        //Evolution steps query
        else if(query == E_STEPS){
            //Steps keeps track of the number of steps the evolution takes
            int steps = 0;
            //Define variables to handle additional input
            cin >> source_gene >> target_gene;
            //Print out the numerical result from evolution_steps()
            cout << "It will take ";
            cout << evolution_steps(genes, num_genes, 
            index_helper(genes, num_genes, source_gene), target_gene, &steps);
            cout << " evolutionary steps to get from " << source_gene;
            cout << " to " << target_gene << endl;
        }
        //Energetic evolution query
        else if(query == ENE_EVOLVE){
            //Define variables to handle additional input
            cin >> source_gene >> target_gene >> cost;
            //Used_energy keeps track of the total amount of energy required
            int used_energy = 0;
            //If energetic_evolution() returns true, print it out
            if(energetic_evolution(genes, num_genes, 
            index_helper(genes, num_genes, source_gene), target_gene, 
            cost, &used_energy))
            {
                cout << source_gene << " can evolve into " << target_gene; 
                cout << " with at most " << cost << " evolutionary cost" << endl;
            }
            //Otherwise, print out false
            else
            {
                cout << source_gene << " cannot evolve into " << target_gene;
                cout << " with at most " << cost << " evolutionary cost";
                cout << endl;
            }
        }
        //Evolutionary path query
        else if(query == PATH){
            //Define variables to handle additional input
            cin >> source_gene >> target_gene;
            //Counter, iteration, and gene_path keep track of the number
            //of genes and specific gene sequences the evolution takes
            int counter = 0;
            int iteration = 0;
            string gene_path[num_genes];
            //If this specific evolution is possible, call the helper function
            if(evo_path(genes, num_genes, 
            index_helper(genes, num_genes, source_gene), 
            target_gene, &counter, gene_path))
            {
                evo_path_helper(gene_path, counter, &iteration);
            }
            //Otherwise, cout that the evolution is not possible
            else
            {
                cout << "There is no path from " << source_gene << " to ";
                cout << target_gene << endl;
            }

        }
        //If command is unrecognized
        else{
            cout << query << " not recognized." << endl;}
        //Prompt user again
        cout << endl << "Enter a query: ";
        cin >> query;}
}

  /* index_helper
   * Input: An array of Gene structs, total
   * number of genes, and a specific gene sequence
   * Description: Recursively search through array of genes 
   * until a match is found for the inputted gene sequece
   * Output: Pointer to a gene we are looking for
   */
Gene *index_helper(Gene *genes, int num_genes, string gene)
{
    //Variable to hold the index of the found gene in the array
    int index_of_gene = index_of(genes, gene, num_genes);
    //If the gene can't be found, return nullptr
    if(index_of_gene == -1)
    {
        return nullptr;
    }
    //Otherwise, return a pointer to the correct location in genes array
    else
    {
        return &genes[index_of_gene];
    }
}

  /* clear_seen
   * Input: An array of Gene structs and total number of genes
   * Description: Loop through array of genes and set the 'seen'
   * variable to false for each gene
   * Output: None (void)
   */
void clear_seen(Gene *genes, int num_genes)
{
    //Loop through array and set each gene's 'seen' variable to false
    for(int i = 0; i < num_genes; i++)
    {
        genes[i].seen = false;
    }
}
  /* print_query
   * Input: An array of Gene structs and total
   * number of genes
   * Description: Print out data from provided array of genes
   * Output: None (void)
   */
void print_query(Gene *genes, int num_genes)
{
    //Loop through each gene
    for(int i = 0; i < num_genes; i++)
    {
        cout << "== " << genes[i].sq << " ==" << endl;
        cout << "Mutations:" << endl;
        //If a gene has no mutations
        if(genes[i].mut_count == 0)
        {
            cout << "None" << endl;
        }
        //Loop through each gene's mutations and print them out
        else
        {
            cout << genes[i].mut.target->sq << " - ";
            cout << "Cost: " << genes[i].mut.cost << endl;
        }
    }
}

  /* can_evolve
   * Input: An array of Gene structs, total number of genes, 
   * a pointer to a source gene, and a string of the target gene's sequence.
   * Description: Recursively determine if the source gene is able
   * to evolve into the target one.
   * Output: Boolean value of whether or not the evolution is possible.
   */
bool can_evolve(Gene *genes, int num_genes, Gene *src, string tgt)
{
    //If the source gene is null, return false
    if(src == nullptr){
        return false;}
    //If the source gene has no mutations, return false
    if(src->mut_count == 0){
        return false;}
    //If the source gene can mutate into the target, return true
    else if(tgt == src->mut.target->sq){
        return true;}
    //If the source gene has already been seen, return false
    else if(src->seen == true){
        return false;}
    //Set source gene's seen variable to true
    src->seen = true;
    //Set new_src to the source gene's target and make a recursive call
    Gene *new_src = src->mut.target;
    return can_evolve(genes, num_genes, new_src, tgt);
}

  /* evolution_steps
   * Input: An array of Gene structs, total number of genes, 
   * a pointer to a source gene, a string of the target gene's sequence,
   * and a pointer to an int containing the total number of steps.
   * Description: Recursively compute the total number of steps
   * a given evolution will take.
   * Output: Integer of the total number of required steps.
   */
int evolution_steps(Gene *genes, int num_genes, 
Gene *src, string tgt, int *steps)
{
    //Increment steps by 1
    *steps = *steps + 1;
    //If the source gene is null, return -1
    if(src == nullptr){
        return -1;}
    //If the source gene has no mutations, return -1
    if(src->mut_count == 0){
        return -1;}
    //If the source gene can mutate into the target, return number of steps
    else if(tgt == src->mut.target->sq){
        return *steps;}
    //If the source gene has already been seen, return -1
    else if(src->seen == true){
        return -1;}
    //Set source gene's seen variable to true
    src->seen = true;
    //Set new_src to the source gene's target and make a recursive call
    Gene *new_src = src->mut.target;
    return evolution_steps(genes, num_genes, new_src, tgt, steps);
}

  /* energetic_evolution
   * Input: An array of Gene structs, total number of genes, 
   * a pointer to a source gene, a string of the target gene's sequence,
   * a user-inputted allowed amount (int) of energy, and a pointer to the
   * amount of energy used so far (int)
   * Description: Recursively determine if the source gene is able to mutate
   * into the target with the allowed amount of energy.
   * Output: Boolean of whether or not the evolution is possible with 
   * the energy constaint.
   */
bool energetic_evolution(Gene *genes, int num_genes, Gene *src, 
string tgt, int allowed_energy, int *used_energy)
{
    //If the source gene is null, return false
    if(src == nullptr){
        return false;}
    //If the source gene has no mutations, return false
    if(src->mut_count == 0){
        return false;}
    //Increment used_energy by the amount used in each mutation
    *used_energy = *used_energy + src->mut.cost;
    //If the source gene can mutate into the target
     if(tgt == src->mut.target->sq){
        //If energy used is less than the allowed amount of energy, return true
        if(*used_energy <= allowed_energy){
        return true;}
        //Otherwise return false
        else{return false;}}
    //If the source gene has already been seen, return false
    else if(src->seen == true){
        return false;}
    //Set source gene's seen variable to true
    src->seen = true;
    //Set new_src to the source gene's target and make a recursive call
    Gene *new_src = src->mut.target;
    return energetic_evolution(genes, num_genes, 
    new_src, tgt, allowed_energy, used_energy);
}

  /* evo_path
   * Input: An array of Gene structs, total number of genes, 
   * a pointer to a source gene, a string of the target gene's sequence,
   * a pointer to an int containing the number of mutations made so far,
   * and a string array that will hold mutated gene sequences.
   * Description: Recursively determine if the source gene is able to mutate
   * into the target, while storing the evolutionary path in 
   * the gene_path array.
   * Output: Boolean of whether or not the evolution is possible.
   */
bool evo_path(Gene *genes, int num_genes, Gene *src, 
string tgt, int *counter, string *gene_path)
{
    //If the source gene is null, return false
    if(src == nullptr){
        return false;}
    //Increment the counter and update gene_path to hold the gene sequence
    gene_path[*counter] = src->sq;
    *counter = *counter + 1;
    //If the source gene has no mutations, return false
    if(src->mut_count == 0){
        return false;}
    //If the source gene can mutate into the target, return true
    else if(tgt == src->mut.target->sq){
        //Update gene_path and counter again
        gene_path[*counter] = src->mut.target->sq;
        *counter = *counter + 1;
        return true;}
    //If the source gene has already been seen, return false
    else if(src->seen == true){
        return false;}
    //Set source gene's seen variable to true
    src->seen = true;
    //Set new_src to the source gene's target and make a recursive call
    Gene *new_src = src->mut.target;
    return evo_path(genes, num_genes, new_src, tgt, counter, gene_path);
}

  /* evo_path
   * Input: A string array of gene sequences, an int of the total mutations,
   and a pointer to an int containing the current iteration of the function.
   * Description: Recursively print out the contents of the gene_path array.
   * Output: None (void).
   */
void evo_path_helper(string *gene_path, int counter, int *iteration)
{
    //If the array has been fully printed out
    if(counter == (*iteration + 1))
    {
        //Print out final gene sequence
        cout << gene_path[*iteration] << endl;
    }
    else
    {
        //Print out next gene sequence, increment the iteration variable, 
        //and make recursive call
        cout << gene_path[*iteration] <<  " -> ";
        *iteration = *iteration + 1;
        evo_path_helper(gene_path, counter, iteration);
    }
}