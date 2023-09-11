#include <iostream>     // for cout, cin
#include <fstream>      // for ifstream
#include <sstream>      // for stringstream
#include <filesystem>   	// making inputting files easier
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"

using std::cout;            using std::endl;
using std::ifstream;        using std::stringstream;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;   using std::cin;

/*
 * This is the function you will be implementing parts of. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */

// TODO: ASSIGNMENT 2 TASK 5:
// Please implement the following function, which should take in two sets of strings
// and returns the number of common strings between the two sets. You should use 
// lambdas and std::count_if.
// Estimated length: <4 lines

///////////////////////////////////////////////////////////////////////////////////////////////////
// BEGIN STUDENT CODE HERE
int numCommonLinks(const unordered_set<string>& curr_set, const unordered_set<string>& target_set) {
    // replace all of these lines!
    (void) target_set;
    (void) curr_set;
    return 0; 
}
// END STUDENT CODE HERE
///////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    WikiScraper w;

    /* Create alias for container backing priority_queue */
    using container = vector<vector<string>>;
    unordered_set<string> target_set = w.getLinkSet(end_page);

    // TODO: ASSIGNMENT 2 TASK 6:
    // Please implement the comparator function that will be used in the priority queue.
    // You'll need to consider what variables this lambda will need to capture, as well as
    // what parameters it'll take in. Be sure to use the function you implemented in Task 1!
    // Estimated length: <3 lines
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // BEGIN STUDENT CODE HERE
    auto cmp_fn = [&w, &target_set](const vector<string>& left, const vector<string>& right) {
        // replace all of these lines.
        (void) w;
        (void) target_set;
        (void) left;
        (void) right;
        return false; // replace this line! make sure to use numCommonLinks.
    };
    // END STUDENT CODE HERE
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    // TODO: ASSIGNMENT 2 TASK 7:
    // Last exercise! please instantiate the priority queue for this algorithm, called "queue". Be sure 
    // to use your work from Task 2, cmp_fn, to instantiate our queue. 
    // Estimated length: 1 line
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // BEGIN STUDENT CODE HERE
    // something like priority_queue<...> queue(...);
    // please delete ALL 4 of these lines! they are here just for the code to compile.
    std::priority_queue<vector<string>> queue;
    throw std::invalid_argument("Not implemented yet.\n");
    return {};

    // END STUDENT CODE HERE
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    queue.push({start_page});
    unordered_set<string> visited;

    while(!queue.empty()) {
        vector<string> curr_path = queue.top();
        queue.pop();
        string curr = curr_path.back();

        auto link_set = w.getLinkSet(curr);

        /*
         * Early check for whether we have found a ladder.
         * By doing this check up here we spead up the code because
         * we don't enqueue every link on this page if the target page
         * is in the links of this set.
         */
        if(link_set.find(end_page) != link_set.end()) {
            curr_path.push_back(end_page);
            return curr_path;
        }

        for(const string& neighbour : link_set) {
            if(visited.find(neighbour) == visited.end()) {
                visited.insert(neighbour);
                vector<string> new_path = curr_path;
                new_path.push_back(neighbour);
                queue.push(new_path);
            }
        }
    }
    return {};
}

int main() {
    // a quick working directory fix to allow for easier filename inputs
    auto path = std::filesystem::current_path() / "res/";
    std::filesystem::current_path(path);
    std::string filenames = "Available input files: ";

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::string filename = entry.path().string();
        filename = filename.substr(filename.rfind("/") + 1);
        filenames += filename + ", ";
    }
    // omit last ", ".
    cout << filenames.substr(0, filenames.size() - 2) << "." << endl;

    /* Container to store the found ladders in */
    vector<vector<string>> outputLadders;

    cout << "Enter a file name: ";
    string filename;
    getline(cin, filename);

    ifstream in(filename);
    int numPairs;
    // parse the first line as the number of tokens
    in >> numPairs;

    // loop through each line, parsing out page names and calling findWikiLadder
    string startPage, endPage;
    for (int i = 0; i < numPairs; i++) {
        // parse the start and end page from each line
        in >> startPage >> endPage;
        outputLadders.push_back(findWikiLadder(startPage, endPage));
    }

    /*
     * Print out all ladders in outputLadders.
     * We've already implemented this for you!
     */
    for (auto& ladder : outputLadders) {
        if(ladder.empty()) {
            cout << "No ladder found!" << endl;
        } else {
            cout << "Ladder found:" << endl;
            cout << "\t" << "{";

            std::copy(ladder.begin(), ladder.end() - 1,
                      std::ostream_iterator<string>(cout, ", "));
            /*
             * The above is an alternate way to print to cout using the
             * STL algorithms library and iterators. This is equivalent to:
             *    for (size_t i = 0; i < ladder.size() - 1; ++i) {
             *        cout << ladder[i] << ", ";
             *    }
             */
            cout << ladder.back() << "}" << endl;
        }
    }
    return 0;
}




