#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char ** args) {

	srand(time(NULL));
        if (argc < 3) {
	                cout << "Usage: gen [n] [m] [file]\n";
					exit(1);
					        }

						        int n = atoi(args[1]);
							        int m = atoi(args[2]);

								        if (m < n) {
									                cout << "M must be >= N\n";
													exit(1);
													        }

														        string airports[n];

															        for (int i = 0; i < n; i++) {
																                airports[i] += 'A' + (i / (26 * 26)) % 26;
																		                airports[i] += 'A' + (i / 26) % 26;
																				                airports[i] += 'A' + i % 26;
																						        }

																							        ofstream out;
																								        out.open(args[3]);
																									        out << fixed;
																										        out.precision(2);

																											        out << "1\n";
																												        out << n << " " << m << "\n";

																													        for (int i = 0; i < n; i++) {
																														                out << airports[i] << " " << airports[rand() % n] << " " << (rand() % 100000) * 0.01 << "\n";
																																        }

																																	        for (int i = 0; i < m - n; i++) {
																																		                out << airports[rand() % n] << " " << airports[rand() % n] << " " << (rand() % 100000) * 0.01 << "\n";
																																				        }

																																					        for (int i = 0; i < 10; i++) {
																																						                out << airports[rand() % n] << " " << airports[rand() % n] << "\n";
																																								        }

																																									        out << "END\n";

																																										        out.close();
																																											}
