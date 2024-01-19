/*
 * mutations.cpp
 * purpose: Allow user to see possible mutations
 * of a provided set of genes
 * author: Zach Meyers
 * last modified: 03/10/23
 */

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

//Define max number of possible mutations
const int MAX_MUTATIONS = 5;

//Define Gene and Monster structs
struct Gene;
struct Mutation
{
    string name;
    Gene *parent;
    int cost;
};
struct Gene
{
    string name;
    int num_mutations;
    Mutation possible_mutations[MAX_MUTATIONS];
};

//Define functions
Gene *read_file(string filename, int *num_genes);
void initialize_genes(Gene *genes, int num_genes);
void fill_genes(Gene *genes, int num_genes, string filename);
void prompt_and_execute(Gene *genes, int num_genes);
void print_query(Gene *genes, int num_genes);
void mutation_query(Gene *genes, int num_genes, 
string req_gene, string req_mutation);
void mutation_energy_query(Gene *genes, int num_genes, 
string req_gene, string req_mutation, int req_energy);

int main(int argc, char *argv[])
{
    //If user doesn't provide a filename
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }

    //Create variables to hold filename and 
    //total number of genes in file
    string filename = argv[1];
    int num_genes;

    //Call read_file to fill all_genes array,
    //and start the prompt_and_execute loop
    Gene *all_genes = read_file(filename, &num_genes);
    prompt_and_execute(all_genes, num_genes);

    //Clear memory
    delete [] all_genes;

    return 0;
}

  /* read_file
   * Input: A filename and a pointer to a variable holding
   * the total number of genes in the file
   * Description: Open file and call helper functions to 
   * fill an array of Gene structs
   * Output: Filled array of Gene structs
   */
Gene *read_file(string filename, int *num_genes)
{
    ifstream infile;
    infile.open(filename);

    //Check if file opened correctly
    if(infile.fail())
    {
        cerr << "ERROR: The file " << filename << " failed to open correctly." << endl;
        exit(EXIT_FAILURE);
    }
    //Read in number of mutations
    infile >> *num_genes;
    //Create array to hold genes, and call helper functions
    Gene *all_genes = new Gene[*num_genes];
    initialize_genes(all_genes, *num_genes);
    infile.close();
    fill_genes(all_genes, *num_genes, filename);
    return all_genes;

}


  /* initialize_genes
   * Input: An array of Gene structs and total
   * number of genes
   * Description: Initialize every Gene and Mutation
   * variable in the array
   * Output: None (void)
   */
void initialize_genes(Gene *genes, int num_genes)
{
    //Loop through each gene
    for(int i = 0; i < num_genes; i++)
    {
        //Set each gene's name to empty string
        genes[i].name = "";
        genes[i].num_mutations = 0;
        //Loop through each mutation
        for(int j = 0; j < MAX_MUTATIONS; j++)
        {
            //Initialize each mutation's struct variables
            genes[i].possible_mutations[j].name = "";
            genes[i].possible_mutations[j].parent = nullptr;
            genes[i].possible_mutations[j].cost = 0;
        }
    }
}


  /* fill_genes
   * Input: An array of Gene structs, total
   * number of genes, and a filename
   * Description: Fill array of Gene structs with 
   * data from provided file
   * Output: None (void)
   */
void fill_genes(Gene *genes, int num_genes, string filename)
{
    ifstream infile;
    infile.open(filename);
    //First pass: fill genes array with names
    string trash_1 = "";
    string trash_2 = "";
    infile >> trash_1;
    //Fill array with names and skip over rest of line
    for(int i = 0; i < num_genes; i++)
    {
        infile >> genes[i].name;
        getline(infile, trash_2);
    } 
    infile.close();

    //Second pass: fill genes with each mutation
    int num_mutations;
    infile.open(filename);
    infile >> trash_1;

    //Loop through each gene
    for(int i = 0; i < num_genes; i++)
    {
        //Fill each genes struct with number of possible mutations
        infile >> trash_2;
        infile >> num_mutations;
        genes[i].num_mutations = num_mutations;
        
        //Loop through each gene's possible mutations
        for(int j = 0; j < num_mutations; j++)
        {
            //Fill each mutation with its name, price, 
            //and a pointer to its parent gene
            string each_mutation;
            int each_price;
            infile >> each_mutation >> each_price;
            genes[i].possible_mutations[j].name = each_mutation;
            genes[i].possible_mutations[j].cost = each_price;
            genes[i].possible_mutations[j].parent = &genes[i];
        }
    }
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
    string query;
    string source_gene;
    string target_gene;
    int energy;

    //Prompt user for input
    cout << "Enter a query: ";
    cin >> query;

    //While quit command is not entered
    while(query != "q")
    {
        //Print query
        if(query == "p")
        {
            print_query(genes, num_genes);
        }
        //Mutation query
        else if(query == "m")
        {
            cin >> source_gene >> target_gene;
            mutation_query(genes, num_genes, source_gene, target_gene);
        }
        //Mutation with energy query
        else if(query == "me")
        {
            cin >> source_gene >> target_gene >> energy;
            mutation_energy_query(genes, num_genes, source_gene, target_gene, energy);
        }
        //If command is unrecognized
        else
        {
            cout << query << " not recognized." << endl;
        }
        //Prompt user again
        cout << endl << "Enter a query: ";
        cin >> query;
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
        cout << "== " << genes[i].name << " ==" << endl;
        cout << "Mutations:" << endl;
        //If a gene has no mutations
        if(genes[i].num_mutations == 0)
        {
            cout << "None" << endl;
        }
        //Loop through each gene's mutations and print them out
        for(int j = 0; j < genes[i].num_mutations; j++)
        {
            cout << genes[i].possible_mutations[j].name << " - ";
            cout << "Cost: " << genes[i].possible_mutations[j].cost << endl;
        }

    }

}

  /* mutation_query
   * Input: An array of Gene structs, total
   * number of genes, source gene, and target gene
   * Description: Determine whether a provided source
   * gene can mute into provided target gene
   * Output: None (void)
   */
void mutation_query(Gene *genes, int num_genes, 
string req_gene, string req_mutation)
{
    int gene_pos = -1;
    bool is_found = false;
    //Loop through genes to find the 
    //one we are searching for
    for(int i = 0; i < num_genes; i++)
    {
        if(genes[i].name == req_gene)
        {
            gene_pos = i;
            break;
        }
    }
    //If the gene can't be found
    if(gene_pos == -1)
    {
        cout << req_gene << " cannot mutate into " << req_mutation << endl;
    }
    //If the gene is found
    else
    {
        //Search for the mutation
        for(int i = 0; i < genes[gene_pos].num_mutations; i++)
        {
            //If the mutation is found
            if(genes[gene_pos].possible_mutations[i].name == req_mutation)
            {
                cout << req_gene << " can mutate into " << req_mutation << endl;
                is_found = true;
                break;
            }
        }
        //If loop terminates without finding the mutation
        if(!is_found)
        {
            cout << req_gene << " cannot mutate into " << req_mutation << endl;
        }
    }

}

  /* mutation_energy_query
   * Input: An array of Gene structs, total
   * number of genes, source gene, target gene,
   * and amount of energy
   * Description: Determine whether a provided source
   * gene can mute into provided target gene with
   * a provided amount of energy
   * Output: None (void)
   */
void mutation_energy_query(Gene *genes, int num_genes, 
string req_gene, string req_mutation, int req_energy)
{
    int gene_pos = -1;
    bool is_found = false;
    //Loop through genes to find the 
    //one we are searching for
    for(int i = 0; i < num_genes; i++)
    {
        if(genes[i].name == req_gene)
        {
            gene_pos = i;
            break;
        }
    }
    //If the gene can't be found
    if(gene_pos == -1)
    {
        cout << req_gene << " cannot mutate into " << req_mutation << endl;
    }
    //If the gene is found
    else
    {
        //Search for the mutation
        for(int i = 0; i < genes[gene_pos].num_mutations; i++)
        {
            //If the mutation is found
            if(genes[gene_pos].possible_mutations[i].name == req_mutation)
            {
                //If the inputted cost exceeds the required amount
                if(req_energy >= genes[gene_pos].possible_mutations[i].cost)
                {
                    cout << req_gene << " can mutate into " << req_mutation <<
                    " with evolutionary cost " << req_energy << endl;

                }
                //If the inputted cost isn't enough
                else
                {
                    cout << req_gene << " can mutate into " << req_mutation <<
                    " but not with evolutionary cost " << req_energy << endl;
                }
                is_found = true;
                break;
            }
        }
        //If loop terminates without finding the mutation
        if(!is_found)
        {
            cout << req_gene << " cannot mutate into " << req_mutation << endl;
        }
    }

}

