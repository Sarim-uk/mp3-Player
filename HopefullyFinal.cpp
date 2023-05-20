#include<iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <string.h>
#include<conio.h>

using namespace std;

//Class consisting of attributes of all added songs
class Song {
	
	string songName;
	string artistName;
	string genre;
	string releaseDate;
	string lyrics;
	
public:
	
	Song() {}
	
	void setSongName(const string songName) {
		this->songName = songName;
	}
	
	void setArtistName(const string artistName) {
		this->artistName = artistName;
	}
	
	void setGenre(const string genre) {
		this->genre = genre;
	}
	
	void setReleaseDate(const string releaseDate) {
		this->releaseDate = releaseDate;
	}
	
	void setLyrics(const string lyrics) {
		this->lyrics = lyrics;
	}
	
	const string getSongName() {
		return songName;
	}
	
	const string getArtistName() {
		return artistName;
	}
	
	const string getGenre() {
		return genre;
	}
	
	const string getReleaseDate() {
		return releaseDate;
	}
	
	const string getLyrics() {
		return lyrics;
	}
};

//Node of linked list(Every linked list consists of an album and each node is a song)
class node {
public:
	Song aa;
	node* next;
	node* prev;
	
	public:
		
		node() {
			next = NULL;
			prev = NULL;
		}
		
		friend class linkedList;
};

//Linked List consisting of an album
class linkedList {
public:
	node* root;
		
		linkedList() {
			root = NULL;
		}
		
		//Inserting songs at each node of linked list	
		void insertNode(Song* ss) {
			node* newNode = new node;
			newNode->aa.setSongName(ss->getSongName());
			newNode->aa.setArtistName(ss->getArtistName());
			newNode->aa.setGenre(ss->getGenre());
			newNode->aa.setReleaseDate(ss->getReleaseDate());
			newNode->aa.setLyrics(ss->getLyrics());
			
			if(root == NULL) {
				root = newNode;
			} else {
				node* temp = root;
				while(temp->next != NULL) {
					temp->prev = temp;
					temp = temp->next;
				}
				
				temp->next = newNode;
			}
		}
		
		//Traversing linked list and printing all the songs in that list
		void printTraversal() {
			if(root == NULL) {
				cout << "Linked List is empty" << endl;
			} else {
				node* temp = root;
				while(temp->next != NULL) {
					cout << temp->aa.getSongName() << endl;
					temp = temp->next;
				}
				cout << temp->aa.getSongName() << endl;
			}
		}
		
		//Fetching songs by traversing through the linked list
		Song* fetchSong(const string ss) {
			if(root == NULL) {
				return NULL;
			} else {
				node* temp = new node;
				temp = root;
				
				while(temp != NULL) {
					if(temp->aa.getSongName() == ss) {
						return &(temp->aa);
					} else {
						temp = temp->next;
					}
				}
				
				return NULL;
			}
		}
		
		//Displaying information of choosen song
		void displayInformation(const string name) {
			node* temp = new node;
			temp = root;
			
			if(root == NULL) {
				cout << "Song does not exist. Make sure the name is entered correctly!" << endl;
				return;
			} else {
				while(temp != NULL) {
					if(temp->aa.getSongName() == name) {
						cout << "Song name: " << temp->aa.getSongName() << endl;
						cout << "Artist: " << temp->aa.getArtistName() << endl;
						cout << "Genre: " << temp->aa.getGenre() << endl;
						cout << "Release Date: " << temp->aa.getReleaseDate() << endl;
						cout << "Lyrics: " << temp->aa.getLyrics() << endl;
						cout << "--------------------------------------------------------------------------" << endl << endl;
						if(temp->next != NULL)
						cout << endl << "Next song in the playlist: " << temp->next->aa.getSongName() << endl << endl;
						break;
					} else {
						temp = temp->next;
					}
				}
				
				if(temp == NULL) {
					cout << "[Error 404!]" << endl << "Requested song not found. Please re-check spelling!" << endl;
				}
			}
		}
		
		//Merge sort to sort songs by artists
		void sortArtist(node** headRef) {
	    node* head = *headRef;
	    node* a;
	    node* b;
	 
	    /* Base case -- length 0 or 1 */
	    if ((head == NULL) || (head->next == NULL)) {
	        return;
	    }
	 
	    /* Split head into 'a' and 'b' sublists */
	    FrontBackSplit(head, &a, &b);
	 
	    /* Recursively sort the sublists */
	    sortArtist(&a);
	    sortArtist(&b);
	 
	    /* answer = merge the two sorted lists together */
	    *headRef = SortedMergeArt(a, b);
	}

	node* SortedMergeArt(node* a, node* b) {
	    node* result = NULL;
	 
	    if (a == NULL)
	        return (b);
	    else if (b == NULL)
	        return (a);
	        
	    string cmp = a->aa.getArtistName();
	    string cmp2 = b->aa.getArtistName();
	    
	    if (cmp[0] <= cmp2[0]) {
	        result = a;
	        result->next = SortedMergeArt(a->next, b);
	    }
	    else {
	        result = b;
	        result->next = SortedMergeArt(a, b->next);
	    }
	    return (result);
	}

	void FrontBackSplit(node* source, node** frontRef, node** backRef) {
	    node* fast;
	    node* slow;
	    slow = source;
	    fast = source->next;
	 
	    while (fast != NULL) {
	        fast = fast->next;
	        if (fast != NULL) {
	            slow = slow->next;
	            fast = fast->next;
	        }
	    }
	
	    *frontRef = source;
	    *backRef = slow->next;
	    slow->next = NULL;
	}
	
	//Merge sort to sort songs by song name
	void sortSongs(node** headRef) {
	    node* head = *headRef;
	    node* a;
	    node* b;
	 
	    /* Base case -- length 0 or 1 */
	    if ((head == NULL) || (head->next == NULL)) {
	        return;
	    }
	 
	    /* Split head into 'a' and 'b' sublists */
	    FrontBackSplit(head, &a, &b);
	 
	    /* Recursively sort the sublists */
	    sortSongs(&a);
	    sortSongs(&b);
	 
	    /* answer = merge the two sorted lists together */
	    *headRef = SortedMergeSon(a, b);
	}

	node* SortedMergeSon(node* a, node* b) {
	    node* result = NULL;
	 
	    if (a == NULL)
	        return (b);
	    else if (b == NULL)
	        return (a);
	        
	    string cmp = a->aa.getSongName();
	    string cmp2 = b->aa.getSongName();
	    
	    if (cmp[0] <= cmp2[0]) {
	        result = a;
	        result->next = SortedMergeSon(a->next, b);
	    }
	    else {
	        result = b;
	        result->next = SortedMergeSon(a, b->next);
	    }
	    return (result);
	}
	
	//Merge sort to sort songs by song lyrics
	void sortLyrics(node** headRef) {
	    node* head = *headRef;
	    node* a;
	    node* b;
	 
	    /* Base case -- length 0 or 1 */
	    if ((head == NULL) || (head->next == NULL)) {
	        return;
	    }
	 
	    /* Split head into 'a' and 'b' sublists */
	    FrontBackSplit(head, &a, &b);
	 
	    /* Recursively sort the sublists */
	    sortLyrics(&a);
	    sortLyrics(&b);
	 
	    /* answer = merge the two sorted lists together */
	    *headRef = SortedMergeLyr(a, b);
	}

	node* SortedMergeLyr(node* a, node* b) {
	    node* result = NULL;
	 
	    if (a == NULL)
	        return (b);
	    else if (b == NULL)
	        return (a);
	        
	    string cmp = a->aa.getLyrics();
	    string cmp2 = b->aa.getLyrics();
	    
	    if (cmp[0] <= cmp2[0]) {
	        result = a;
	        result->next = SortedMergeLyr(a->next, b);
	    }
	    else {
	        result = b;
	        result->next = SortedMergeLyr(a, b->next);
	    }
	    return (result);
	}

	void searchByLyrics(string ss) {
		if(root == NULL) {
			return;
		} else {
		
			node* temp = new node;
			temp = root;
			
			while(temp->next != NULL) {
				string imp = temp->aa.getLyrics();
				size_t ind = imp.find(ss);
				
				if(ind != string::npos) {
					cout << "Keyword found in this song..." << endl;
					cout << "Index found at: " << ind << endl << endl;
					cout << "Song name: " << temp->aa.getSongName() << endl;
					cout << "Artist name: " << temp->aa.getArtistName() << endl;
					cout << "Genre: " << temp->aa.getGenre() << endl;
					cout << "Release date: " << temp->aa.getReleaseDate() << endl;
					cout << "Lyrics: " << temp->aa.getLyrics() << endl;
					cout << endl << endl;
					
					temp = temp->next;
				} else {
					temp = temp->next;
				}
			}
			return;
		}		
	}

};
//Node of binary tree(Each node of binary tree consists of a linked list which is an album) 
class binaryNode {
public:
	linkedList ll;
	binaryNode* left;
	binaryNode* right;
	
	public:
		binaryNode() {
			left = NULL;
			right = NULL;
		}
		
		friend class binaryTree;
};

//Node dedicated for the last played linked list
class lpNode {
	string name;
	lpNode* next;
	
	public:
		
		lpNode() {
			name = "\0";
			next = NULL;
		}
		
	friend class lastPlayed;
};

//Linked list consisting of recently played song
class lastPlayed {
	lpNode* root;
	
	public:
		
		lastPlayed() {
			root = NULL;
		}
		
		//Inserting nodes in the last played linked list
		void insert(const string ss) {
			lpNode* newNode = new lpNode;
			newNode->name = ss;
			
			if(root == NULL) {
				root = newNode;
			} else {
				lpNode* temp = new lpNode;
				temp = root;
				
				while(temp->next != NULL) {
					temp = temp->next;
				}
				
				temp->next = newNode;
			}
		}
		
		//Displaying all the last played songs
		void displayAll() {
			lpNode* temp = new lpNode;
			temp = root;
			
			if(root == NULL) {
				return;
			} else {
				cout << "Your last played songs...." << endl;
				while(temp->next != NULL) {
					cout << temp->name << endl;
					temp = temp->next;
				}
			}
		}
};

//Binary tree consisting of linked list at each node
class binaryTree {
	public:
	binaryNode* root;
	lastPlayed lp;
	
	public:
		binaryTree() {
			root = NULL;
		}
		
		//Insertion of albums in the binary tree
		void insertNode(linkedList* rec) {
			binaryNode* newNode = new binaryNode;
			newNode->ll = *rec;
			
			if(root == NULL) {
				root = newNode;
			} else {
				
				binaryNode* temp = root;
		      	string val2 = newNode->ll.root->aa.getSongName();
				while (temp != NULL) {
		      		string val1 = temp->ll.root->aa.getSongName();
			        if ((val2[0] < val1[0]) && (temp->left == NULL)) {
			          temp->left = newNode;
			          break;
			        } else if (val2[0] < val1[0]) {
			          temp = temp->left;
			        } else if ((val2[0] > val1[0]) && (temp->right == NULL)) {
			          temp->right = newNode;
			          break;
			        } else if((val2[0] == val1[0])) {
			        	if(val2[1] < val1[1] && temp->left == NULL) {
			        		temp->left = newNode;
						} else if(val2[1] < val1[1]) {
							temp = temp->left;
						} else if(val2[1] > val1[1] && temp->right == NULL) {
							temp->right = newNode;
						} else {
							temp = temp->right;
						}
					} 
					else {
			          temp = temp->right;
			        }
			    }
			}
		}
		
		//Printing all the album names
		void print(binaryNode* r) {
			if(r == NULL) {
			return;
		}
		
		cout << r->ll.root->aa.getSongName() << endl;
		cout << endl;
		
		print(r->left);

		print(r->right);
		}
		
		void PlayMusic(string ss) {
			
		lp.insert(ss);
		int n;
		
		//Using objects from time library
		time_t t1;
		time_t t2;
		time_t prevPauseTime = 0;
	
		string msg = "open \"" + ss + "\" type mpegvideo alias " + ss;
		mciSendString(msg.c_str(), NULL, 0, 0);
		int pos = 0;
		char *buff = new char[10];
	    string msg1 = "play " + ss + " from " + itoa(pos,buff,10);
	    lp.displayAll();
	    cout << endl << endl;
	    
	    //Menu for playing file
		while(1) {
			cout << "Press 1 to play the file and press 2 to exit the file." << endl;
			cin>>n;
			if(n==1) {
				t1 = time(0);
				
			    string msg1 = "play " + ss + " from " + itoa(pos,buff,10);
			    mciSendString(msg1.c_str(), NULL, 0, 0);
			    delete [] buff;
		     } else if(n==2) {
				string msg2 = "stop " + ss;
	            mciSendString(msg2.c_str(), NULL, 0, 0);
				user();	
			    break;
			}
			
			//Menu displayed while playing songs			
			while(1) {  
				cout << "Press 0 to pause the file" << endl << "Press 1 to resume the file" << endl << "Press 2 to replay the file" << endl << "Press 3 to exit the file" << endl;
				cin>>n;
				if(n==0) {
					t2 = time(0);
					string msg3 = "pause " + ss;
		            mciSendString(msg3.c_str(), NULL, 0, 0);
		            
		            cout << "Music paused at " << t2 - t1 + prevPauseTime << " seconds..." << endl << endl;
		            prevPauseTime += t2 - t1;
				} else if(n==1) {
					
		            string msg5 = "resume " + ss;
		            mciSendString(msg5.c_str(), NULL, 0, 0);
				
				}
				else if(n==3) {
					string msg4 = "close " + ss;
		            mciSendString(msg4.c_str(), NULL, 0, 0);
		            user();
					break;
				} else if(n==2) {
					mciSendString(msg1.c_str(), NULL, 0, 0);				
				}
			}
			break;
		}
	}
	
	void searchPlaylist(const string ss) {
		
		//Variable for song selection
		string PlaySelection;
		string add = ".mp3";
		
		binaryNode* temp = new binaryNode;
		temp = root;
		
		//Searching for the song
		if(root == NULL) {
			cout << "No playlists found in database....." << endl;
		} else {
			
			while(temp != NULL) {
				string tt = temp->ll.root->aa.getSongName();
				if(ss == tt) {
					temp->ll.printTraversal();
					
					//User selection for playing songs
					cout << endl << "Select a song to play: " << endl;
					fflush(stdin);
					getline(cin, PlaySelection);
					cout << endl << endl;
					
					//Displaying information about the song requested
					temp->ll.displayInformation(PlaySelection);
					
					//Multimedia function to play songs
					PlayMusic(PlaySelection.append(add));
					return;
				} else if(ss[0] < tt[0]) {
					temp = temp->left;
				} else if(ss[0] > tt[0]) {
					temp = temp->right;
				} else if(ss[0] == tt[0]) {
					if(ss[1] < tt[1]) {
						temp = temp->left;
					} else {
						temp = temp->right;
					}
				}
			}
		}
	}
	
	void user() {
		string SearchSelection;
		int mainSelection;
		
		//Main user interaction panel
		cout << endl << endl << "-----------USER SECTION-----------" << endl << endl << endl;
		
		time_t curr_time;
		curr_time = time(NULL);
	
		tm *tm_local = localtime(&curr_time);
		cout << "Current local time: " << tm_local->tm_hour << ":" << tm_local->tm_min << ":" << tm_local->tm_sec << endl;
	
		cout << "Welcome to Spotify (trust us this is the real one)" << endl << endl;
		cout << "Select an option: " << endl;
		cout << "1. Play Music: " << endl;
		cout << "2. Sort Playlists: " << endl;
		cout << "3. Create a new playlist: " << endl;
		cout << "4. Delete a playlist: " << endl;
		cout << "5. Search by lyrics: " << endl;
		cout << "6. Exit Player: " << endl;
		cin >> mainSelection;
		
		switch(mainSelection) {
			
			case 1: {
				cout << "Current available playlists: " << endl << endl;
				print(root);
				
				cout << endl << "Select a playlist to expand songs....." << endl;
				fflush(stdin);
				getline(cin, SearchSelection);
				
				//Printing all available songs in the requested playlist
				cout << endl << endl << "Songs available in " << SearchSelection << " playlist: " << endl;
				//Searching the playlist for the requested song
				searchPlaylist(SearchSelection);
				cout << endl << endl;
				break;
			}
			
			case 2: {
				int sortOption;
				
				cout << "Select the sort you want to apply: " << endl;
				cout << "1. Sort by artist name..." << endl;
				cout << "2. Sort by song name..." << endl;
				cout << "3. Sort by lyrics..." << endl;
				cin >> sortOption;
				
				if(sortOption == 1) {
					cout << "Playlists after sorting: " << endl;
					sortPlaylistArt(root);
				} 
				
				else if(sortOption == 2) {
					cout << "Playlist songs after sorting:" << endl;
					sortPlaylistSong(root);
				}
				
				else if(sortOption == 3) {
					cout << "Playlist songs after sorting by lyrcs:" << endl;
					sortPlaylistLyr(root);
				}
				
				user();
				break;
			}
			
			case 3: {
				string songSelect;
				cout << "Songs available in the database: " << endl;
				showSongs(root);
				
				linkedList* oo = new linkedList;
				
				while(songSelect != "1") {
					cout << "Enter song name to enter to your new playlist: " << endl;
					cout << "Enter 1 to stop adding songs: " << endl;
					fflush(stdin);
					getline(cin, songSelect);
					
					fetch(root, songSelect, oo);
				}

				insertNode(oo);
				
				user();
				break;
			}
			
			case 4: {
				string selectPlaylist;
				cout << "Enter the playlist name you want to delete: " << endl << endl;
				print(root);
				cout << endl;
				fflush(stdin);
				getline(cin, selectPlaylist);
				deletePlaylist(root, selectPlaylist);
				
				cout << endl << "Playlists available after deletion: " << endl;
				print(root);
				cout << endl;
				user();
				break;
			}
			
			case 5: {
				string ss;
				
				cout << "Enter the part of the lyrics you remember..." << endl;
				fflush(stdin);
				getline(cin, ss);
				
				searchLyrics(root, ss);
				
				user();
				break;
			}
			
			case 6: {
				return;
				break;
			}
			
			default: {
				cout << "[ERROR]" << endl << "Enter a valid option! Try again!" << endl << endl;
				user();
				break;
			}
		}
	}
	
	//Extracting a specific song object from the whole database
	binaryNode* fetch(binaryNode* r, const string ss, linkedList* obj) {
		if(r == NULL) {
			return NULL;
		}
		
		fetch(r->left, ss, obj);
		
		if(r->ll.fetchSong(ss) != NULL) {
			obj->insertNode(r->ll.fetchSong(ss));
		}
		
		fetch(r->right, ss, obj);
	}
	
	//Searching for and deleting a playlist
	binaryNode* deletePlaylist(binaryNode* r, string selectPlaylist) {
	
	string cmp = selectPlaylist;
    string cmp2 = r->ll.root->aa.getSongName();

    if (r == NULL) {
      return NULL;
    }   
    else if (cmp[0] < cmp2[0]) {
      r -> left = deletePlaylist(r->left, selectPlaylist);
    }
    else if (cmp[0] > cmp2[0]) {
      r -> right = deletePlaylist(r->right, selectPlaylist);
    }
    else {
      if (r->left == NULL) {
        binaryNode* temp = r->right;
        delete r;
        return temp;
      } else if (r->right == NULL) {
        binaryNode* temp = r->left;
        delete r;
        return temp;
      } else {
        binaryNode * temp = minValueNode(r->right);
        r->ll = temp->ll;
        r->right = deletePlaylist(r->right, selectPlaylist);
      }
    }
    return r;
  }
  
  //Getting the minimum node for deletion from subtrees
  binaryNode * minValueNode(binaryNode* node) {
    binaryNode* current = node;
    while (current->left != NULL) {
      current = current->left;
    }
    return current;
  }
	
	//Sorting the playlists according to Artist
	binaryNode* sortPlaylistArt(binaryNode* r) {
		if(r == NULL) {
			return NULL;
		}
		
		r->ll.sortArtist(&(r->ll.root));
		r->ll.printTraversal();
		cout << endl;
		sortPlaylistArt(r->left);		
		sortPlaylistArt(r->right);
	}
	
	//Sorting the playlists according to songs
	binaryNode* sortPlaylistSong(binaryNode* r) {
		if(r == NULL) {
			return NULL;
		}
		
		r->ll.sortSongs(&(r->ll.root));
		r->ll.printTraversal();
		cout << endl;
		sortPlaylistSong(r->left);
		sortPlaylistSong(r->right);
	}
	
	//Sorting the playlists according to lyrics
	binaryNode* sortPlaylistLyr(binaryNode* r) {
		if(r == NULL) {
			return NULL;
		}
		
		r->ll.sortLyrics(&(r->ll.root));
		r->ll.printTraversal();
		cout << endl;
		sortPlaylistLyr(r->left);
		sortPlaylistLyr(r->right);
	}
	
	//Showing all the songs stored in the binary trees
	binaryNode* showSongs(binaryNode* r) {
		if(r == NULL) {
			return NULL;
		}
		
		showSongs(r->left);
		
		r->ll.printTraversal();
		cout << endl;
		
		showSongs(r->right);
	}
	
	binaryNode* searchLyrics(binaryNode* r, const string search) {
		if(r == NULL) {
			return NULL;
		}
		
		searchLyrics(r->left, search);
		
		r->ll.searchByLyrics(search);
		
		searchLyrics(r->right, search);
	}
};

int main() {
	
	//Storing songs in objects, then passing them as nodes of a linked list, then the linked list is stored in BST.
	Song ss[38];
	ss[0].setSongName("Tuesday");
	ss[0].setArtistName("Burak Yeter");
	ss[0].setGenre("House");
	ss[0].setReleaseDate("25/11/2022");
	ss[0].setLyrics("Got the club going up, on a Tuesday Got your girl in the cut, and she aint choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up Got the club going up Got the club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up Got the club going up Always workin' OT, overtime and outta town Things is crazy back home, it kills me that I'm not around I think we gettin' too deep, ain't no party on the weekend Upstairs I got Xans in an Advil bottle, I don't take the shit But you do, so I got 'em Got the club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up");

	ss[1].setSongName("Peace");
	ss[1].setArtistName("Rocksted");
	ss[1].setGenre("Techno");
	ss[1].setReleaseDate("25/11/2022");
	ss[1].setLyrics("Got the club going up, on a Tuesday Got your girl in the cut, and she aint choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up Got the club going up Got the club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up Got the club going up Always workin' OT, overtime and outta town Things is crazy back home, it kills me that I'm not around I think we gettin' too deep, ain't no party on the weekend Upstairs I got Xans in an Advil bottle, I don't take the shit But you do, so I got 'em Got the club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up");

	ss[2].setSongName("Sunshine");
	ss[2].setArtistName("OneRepublic");
	ss[2].setGenre("House");
	ss[2].setReleaseDate("25/11/2022");
	ss[2].setLyrics("Got the club going up, on a Tuesday Got your girl in the cut, and she aint choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up Got the club going up Got the club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up Got the club going up Always workin' OT, overtime and outta town Things is crazy back home, it kills me that I'm not around I think we gettin' too deep, ain't no party on the weekend Upstairs I got Xans in an Advil bottle, I don't take the shit But you do, so I got 'em Got the club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club going up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up, on a Tuesday Got your girl in the cut, and she ain't choosey Club goin up Got the club going up Got the club going up");

	ss[3].setSongName("Alone-Walker");
	ss[3].setArtistName("Alan Walker");
	ss[3].setGenre("Electronic");
	ss[3].setReleaseDate("12/02/2016");
	ss[3].setLyrics("Lost in your mind I wanna know Am I losing my mind? Never let me go If this night is not forever At least we are together I know I'm not alone I know I'm not alone Anywhere, whenever Apart, but still together I know I'm not alone I know I'm not alone I know I'm not alone I know I'm not alone Unconscious mind I'm wide awake Wanna feel one last time Take my pain away If this night is not forever At least we are together I know I'm not alone I know I'm not alone Anywhere, whenever Apart, but still together I know I'm not alone I know I'm not alone I know I'm not alone I know I'm not alone I'm not alone I'm not alone I'm not alone I know I'm not alone I'm not alone I'm not alone I'm not alone (I know I'm not alone)");
	
	ss[4].setSongName("Faded");
	ss[4].setArtistName("Alan Walker");
	ss[4].setGenre("Pop");
	ss[4].setReleaseDate("12/03/2015");
	ss[4].setLyrics("You were the shadow to my light Did you feel us? Another star You fade away Afraid our aim is out of sight Wanna see us Alight Where are you now? Where are you now? Where are you now? Was it all in my fantasy? Where are you now? Were you only imaginary? Where are you now? Atlantis Under the sea Under the sea Where are you now? Another dream The monster’s running wild inside of me I’m faded I’m faded So lost, I’m faded I’m faded So lost, I’m faded These shallow waters never met what I needed I’m letting go a deeper dive Eternal silence of the sea, I’m breathing Alive Where are you now? Where are you now? Under the bright but faded lights You’ve set my heart on fire Where are you now? Where are you now? Where are you now? Atlantis Under the sea Under the sea Where are you now? Another dream The monster’s running wild inside of me I’m faded I’m faded So lost, I’m faded I’m faded So lost, I’m faded");
	
	ss[5].setSongName("The-Spectre");
	ss[5].setArtistName("Alan Walker");
	ss[5].setGenre("Electronic");
	ss[5].setReleaseDate("15/09/2017");
	ss[5].setLyrics("Hello, hello Can you hear me As I scream your name? Hello, hello Do you need me Before I fade away? Is this a place that I call home? To find what I've become Walk along the path unknown We live, we love, we lie Deep in the dark, I don't need the light There's a ghost inside me It all belongs to the other side We live, we love, we lie (We live, we love, we lie) Hello, hello Nice to meet you Voice inside my head Hello, hello I believe you How can I forget? Is this a place that I call home? To find what I've become Walk along the path unknown We live, we love, we lie Deep in the dark, I don't need the light There's a ghost inside me It all belongs to the other side We live, we love, we lie (We live, we love, we lie) We live, we love, we lie");
	
	ss[6].setSongName("On-My-Way");
	ss[6].setArtistName("Alan Walker");
	ss[6].setGenre("Electronic");
	ss[6].setReleaseDate("21/03/2019");
	ss[6].setLyrics("I'm sorry but Don't wanna talk, I need a moment 'fore I go It's nothing personal I draw the blinds They don't need to see me cry 'Cause even if they understand They don't understand So then when I'm finished I'm all 'bout my business and ready to save the world I'm taking my misery Make it my bitch, can't be everyone's favorite girl So take aim and fire away I've never been so wide awake No, nobody but me can keep me safe And I'm on my way The blood moon is on the rise The fire burning in my eyes No, nobody but me can keep me safe And I'm on my way Lo siento mucho (Farru), pero me voy Porque a tu lado me di cuenta que nada soy Y me cansé de luchar y de guerrear en vano De estar en la línea de fuego y de meter la mano Acepto mis errores, también soy humano Y tú no ve' que lo hago porque te amo Pero ya (Ya) no tengo más na' que hacer aquí (aquí) Me voy, llegó la hora 'e partir (partir) De mi propio camino, seguir lejos de ti So take aim and fire away I've never been so wide awake No, nobody but me can keep me safe And I'm on my way The blood moon is on the rise (is on the rise, na-na) The fire burning in my eyes (the fire burning in my eyes) No, nobody but me can keep me safe And I'm on my way I'm on my way Everybody keep me safe Everybody keep me safe Everybody keep me safe Everybody, everybody on my way So take aim and fire away I've never been so wide awake No, nobody but me can keep me safe And I'm on my way The blood moon is on the rise The fire burning in my eyes No, nobody but me can keep me safe");
	
	ss[7].setSongName("Ignite");
	ss[7].setArtistName("Alan Walker");
	ss[7].setGenre("Electronic");
	ss[7].setReleaseDate("11/05/2018");
	ss[7].setLyrics("Fireflies, a million little pieces Feeds the dying light, and brings me back to life In your eyes, I see something to believe in Your hands are like a flame, your palms' the sweetest pain Let the darkness lead us into the light Let our dreams get lost, feel the temperature rise Baby, tell me one more beautiful lie One touch and I ignite Like a starship speeding into the night You and I get lost in the infinite lights Baby, tell me one more beautiful lie One touch and I ignite One touch and I ignite One touch and I ignite So alive, your touch is like the daylight Burning on my skin, it turns me on again You and I, survivors of the same kind But we're the only ones dancing on the sun Let the darkness lead us into the light Let our dreams get lost, feel the temperature rise Baby, tell me one more beautiful lie One touch and I ignite Like a starship speeding into the night You and I get lost in the infinite lights Baby, tell me one more beautiful lie One touch and I ignite One touch and I ignite One touch and I ignite Diamonds are forever, but all we need is just tonight We're monumental tremors that can freeze the speed of life Just like particles that's falling from heaven all over the stars Hear you calling for me, hear you calling me home from afar Let the darkness lead us into the light Let our dreams get lost, feel the temperature rise Baby, tell me one more beautiful lie One touch and I ignite I feel the heat as we collide Like a fever that feels so right So baby, tell me one more beautiful lie One touch and I ignite One touch and I ignite One touch and I ignite One touch and I ignite One touch and I ignite One touch and I ignite");
	
	ss[8].setSongName("Godzilla");
	ss[8].setArtistName("Eminem");
	ss[8].setGenre("Hip hop");
	ss[8].setReleaseDate("28/01/2020");
	ss[8].setLyrics("I can swallow a bottle of alcohol and I'll feel like Godzilla Better hit the deck like the card dealer My whole squad's in here, walkin' around the party A cross between a zombie apocalypse and B-Bobby, The Brain Heenan which is probably the same reason I wrestle with mania Shady's in this bitch, I'm posse'd up Consider it to cross me a costly mistake If they sleepin' on me, the hoes better get insomnia, ADHD, Hydroxycut Pass the Courvoisi' (hey, hey) In AA, with an AK, melee, finna set it like a playdate Better vacate, retreat like a vacay, mayday (ayy) This beat is cray-cray, Ray J, H-A-H-A-H-A Laughin' all the way to the bank, I spray flames They cannot tame or placate the (ayy) Monster You get in my way? I'ma feed you to the monster (yeah) I'm normal during the day, but at night turn to a monster (yeah) When the moon shines like Ice Road Truckers I look like a villain outta those blockbusters Godzilla, fire spitter, monster Blood on the dance floor, and on the Louis V carpet Fire, Godzilla, fire, monster Blood on the dance floor, and on the Louis V carpet I'm just a product of Slick Rick, at Onyx, told 'em lick the balls Had 'em just appalled at so many things that pissed 'em off It's impossible to list 'em all And in the midst of all this I'm in a mental hospital with a crystal ball Tryna see, will I still be like this tomorrow? Risperdal, voices whisper My fist is balled back up against the wall, pencil drawn This is just the song to go ballistic on You just pulled a pistol on the guy with the missile launcher I'm just a Loch Ness, the mythological Quick to tell a bitch screw off like a fifth of Vodka When you twist the top of the bottle, I'm a Monster You get in my way? I'ma feed you to the monster (yeah) I'm normal during the day, but at night turn to a monster (yeah) When the moon shines like Ice Road Truckers I look like a villain outta those blockbusters Godzilla, fire spitter, monster Blood on the dance floor, and on the Louis V carpet Fire, Godzilla, fire, monster Blood on the dance floor, and on the Louis V carpet If you never gave a damn, raise your hand 'Cause I'm about to set trip, vacation plans I'm on point, like my index is, so all you will ever get is The motherfuckin' finger (finger), prostate exam ('xam) How can I have all these fans and perspire? Like a liar's pants, I'm on fire And I got no plans to retire and I'm still the man you admire These chicks are spazzin' out, I only get more handsome and flier I got 'em passin' out like what you do, when you hand someone flyers What goes around, comes around just like the blades on a chainsaw 'Cause I caught the flaps of my dollar stack Right off the bat like a baseball, like Kid Ink Bitch, I got them racks with so much ease that they call me Diddy 'Cause I make bands and I call getting cheese a cakewalk (cheesecake!) Bitch, I'm a player, I'm too motherfuckin' stingy for Cher Won't even lend you an ear, ain't even pretendin' to care But I tell a bitch I'll marry her, if she'll bury her Face on my genital area, the original Richard Ramirez Christian Rivera 'Cause my lyrics never sit well, so they wanna give me the chair Like a paraplegic, and it's scary, call it Harry Carry 'Cause every Tom and Dick and Harry Carry a Merriam motherfuckin' dictionary Got 'em swearin' up and down, they can't spit, this shit's hilarious It's time to put these bitches in the obituary column We wouldn't see eye to eye with a staring problem Get the shaft like a steering column (monster) Trigger happy, pack heat, but it's black ink Evil half of the Bad Meets Evil That means take a back seat Take it back to Fat Beats with a maxi single Look at my rap sheets, what attracts these people Is my gangster, bitch, like Apache with a catchy jingle I stack these chips, you barely got a half-eaten Cheeto Fill 'em with the venom, and eliminate 'em Other words, I Minute Maid 'em I don't wanna hurt 'em, but I did, I'm in a fit of rage I'm murderin' again, nobody will evade I'm finna kill 'em, I'm dumpin' their fuckin' bodies in the lake Obliteratin' everything, incinerate a renegade I'm here to make anybody who want it with the pen afraid But don't nobody want it but they're gonna get it anyway 'Cause I'm beginnin' to feel like I'm mentally ill I'm Atilla, kill or be killed, I'm a killer bee, the vanilla gorilla You're bringin' the killer within me, out of me You don't want to be the enemy of the demon Who went in me, and be on the receiving of me, what stupidity it'd be Every bit of me is the epitome of a spitter When I'm in the vicinity, motherfucker, you better duck Or you finna be dead the minute you run into me A hundred percent of you is a fifth of a percent of me I'm 'bout to fuckin' finish you bitch, I'm unfadable You wanna battle, I'm available, I'm blowin' up like an inflatable I'm undebatable, I'm unavoidable, I'm unevadable I'm on the toilet bowl I got a trailer full of money and I'm paid in full I'm not afraid to pull a-, man, stop Look what I'm plannin' (haha)");
	
	ss[9].setSongName("Lose-Yourself");
	ss[9].setArtistName("Eminem");
	ss[9].setGenre("Hip hop");
	ss[9].setReleaseDate("28/10/2002");
	ss[9].setLyrics("Look If you had One shot Or one opportunity To seize everything you ever wanted In one moment Would you capture it Or just let it slip? Yo His palms are sweaty, knees weak, arms are heavy There's vomit on his sweater already, mom's spaghetti He's nervous, but on the surface he looks calm and ready To drop bombs, but he keeps on forgettin' What he wrote down, the whole crowd goes so loud He opens his mouth, but the words won't come out He's chokin', how, everybody's jokin' now The clocks run out, times up, over, blaow Snap back to reality, ope there goes gravity Ope, there goes Rabbit, he choked He's so mad, but he won't give up that easy? No He won't have it, he knows his whole back's to these ropes It don't matter, he's dope, he knows that, but he's broke He's so stagnant, he knows, when he goes back to this mobile home, that's when it's Back to the lab again, yo, this whole rhapsody Better go capture this moment and hope it don't pass him You better lose yourself in the music, the moment You own it, you better never let it go You only get one shot, do not miss your chance to blow This opportunity comes once in a lifetime You better lose yourself in the music, the moment You own it, you better never let it go You only get one shot, do not miss your chance to blow This opportunity comes once in a lifetime You better His soul's escaping, through this hole that is gaping This world is mine for the taking Make me king, as we move toward a New World Order A normal life is borin', but super stardom's close to post mortem It only grows harder, only grows hotter He blows, it's all over, these hoes is all on him Coast to coast shows, he's known as the Globetrotter Lonely roads, God only knows, he's grown farther from home, he's no father He goes home and barely knows his own daughter But hold your nose 'cause here goes the cold water These hoes don't want him no mo', he's cold product They moved on to the next schmo who flows, he nose dove and sold nada So the soap opera is told and unfolds, I suppose it's old partna, but the beat goes on Da-da-dum, da-dum, da-da You better lose yourself in the music, the moment You own it, you better never let it go You only get one shot, do not miss your chance to blow This opportunity comes once in a lifetime You better lose yourself in the music, the moment You own it, you better never let it go You only get one shot, do not miss your chance to blow This opportunity comes once in a lifetime You better No more games, I'ma change what you call rage Tear this motherfuckin' roof off like two dogs caged I was playin' in the beginnin', the mood all changed I been chewed up and spit out and booed off stage But I kept rhymin' and stepped right in the next cypher Best believe somebody's payin' the Pied Piper All the pain inside amplified by the Fact that I can't get by with my nine to Five and I can't provide the right type of Life for my family 'cause man, these goddamn food stamps don't buy diapers And its no movie, there's no Mekhi Phifer This is my life and these times are so hard And it's getting even harder tryna feed and water my seed, plus Teeter totter, caught up between bein' a father and a prima donna Baby mama drama, screamin' on her, too much For me to wanna stay in one spot, another day of monotony's Gotten me to the point, I'm like a snail I've got To formulate a plot or end up in jail or shot Success is my only motherfuckin' option, failure's not Mom, I love you, but this trailer's got to go, I cannot grow old in Salem's Lot So here I go, is my shot Feet, fail me not, this may be the only opportunity that I got You better lose yourself in the music, the moment You own it, you better never let it go You only get one shot, do not miss your chance to blow This opportunity comes once in a lifetime You better lose yourself in the music, the moment You own it, you better never let it go You only get one shot, do not miss your chance to blow This opportunity comes once in a lifetime You better You can do anything you set your mind to, man");
	
	ss[10].setSongName("Rap-God");
	ss[10].setArtistName("Eminem");
	ss[10].setGenre("Hip hop");
	ss[10].setReleaseDate("14/10/2013");
	ss[10].setLyrics("Look, I was gonna go easy on you not to hurt your feelings But I'm only going to get this one chance (six minutes-, six minutes-) Something's wrong, I can feel it (six minutes, Slim Shady, you're on!) Just a feeling I've got, like something's about to happen, but I don't know what If that means what I think it means, we're in trouble, big trouble And if he is as bananas as you say, I'm not taking any chances You are just what the doc ordered I'm beginnin' to feel like a Rap God, Rap God All my people from the front to the back nod, back nod Now, who thinks their arms are long enough to slap box, slap box? They said I rap like a robot, so call me Rap-bot But for me to rap like a computer, it must be in my genes I got a laptop in my back pocket My pen'll go off when I half-cock it Got a fat knot from that rap profit Made a livin' and a killin' off it Ever since Bill Clinton was still in office With Monica Lewinsky feelin' on his nutsack I'm an MC still as honest But as rude and as indecent as all hell Syllables, skill-a-holic (kill 'em all with) This flippity dippity-hippity hip-hop You don't really wanna get into a pissin' match With this rappity brat, packin' a MAC in the back of the Ac' Backpack rap crap, yap-yap, yackety-yack And at the exact same time, I attempt these lyrical acrobat stunts while I'm practicin' that I'll still be able to break a motherfuckin' table Over the back of a couple of faggots and crack it in half Only realized it was ironic, I was signed to Aftermath after the fact How could I not blow? All I do is drop F-bombs Feel my wrath of attack Rappers are havin' a rough time period, here's a maxi pad It's actually disastrously bad for the wack While I'm masterfully constructing this masterpièce 'Cause I'm beginnin' to feel like a Rap God, Rap God All my people from the front to the back nod, back nod Now, who thinks their arms are long enough to slap box, slap box? Let me show you maintainin' this shit ain't that hard, that hard Everybody want the key and the secret to rap immortality like ? have got Well, to be truthful the blueprint's Simply rage and youthful exuberance Everybody loves to root for a nuisanc Hit the Earth like an asteroid Did nothing but shoot for the Moon since (pew!) MCs get taken to school with this music 'Cause I use it as a vehicle to Bus the rhyme Now I lead a new school full of student  Me? I'm a product of Rakim Lakim Shabazz, 2Pac, N.W.A, Cube, hey Doc, Ren Yella, Eazy, thank you, they got Slim Inspired enough to one day grow up, blow up and be in a position To meet Run-D.M.C., induct them Into the motherfuckin' Rock and Roll Hall of Fame Even though I'll walk in the church and burst in a ball of flames Only Hall of Fame I'll be inducted in is the alcohol of fame On the wall of shame You fags think it's all a game, 'til I walk a flock of flames Off a plank and, tell me what in the fuck are you thinkin'? Little gay-lookin' boy So gay, I can barely say it with a straight face, lookin' boy (ha-ha!) You're witnessin' a mass-occur Like you're watching a church gathering take place, lookin' boy Oy vey, that boy's gay! That's all they say, lookin' boy You get a thumbs up, pat on the back And a Way to go from your label every day, lookin' boy Hey, lookin' boy! What you say, lookin' boy? I get a Hell, yeah from Dre, lookin' boy I'ma work for everything I have, never asked nobody for shit Get outta my face, lookin' boy! Basically, boy, you're never gonna be capable Of keepin' up with the same pace, lookin' boy, 'cause- I'm beginnin' to feel like a Rap God, Rap God All my people from the front to the back nod, back nod The way I'm racin' around the track, call me NASCAR, NASCAR Dale Earnhardt of the trailer park, the White Trash God Kneel before General Zod This planet's Krypton-, no, Asgard, Asgard So you'll be Thor and I'll be Odin You rodent, I'm omnipotent Let off, then I'm reloadin' Immediately with these bombs I'm totin' And I should not be woken I'm the walkin' dead, but I'm just a talkin' head, a zombie floatin' But I got your mom deep-throatin' I'm out my Ramen Noodle We have nothin' in common, poodle I'm a Doberman, pinch yourself in the arm and pay homage, pupil It's me, my honesty's brutal But it's honestly futile if I don't utilize what I do though For good at least once in a while So I wanna make sure somewhere in this chicken scratch I scribble and doodle enough rhymes To maybe try to help get some people through tough times But I gotta keep a few punchlines Just in case 'cause even you unsigned Rappers are hungry lookin' at me like it's lunchtime I know there was a time where once I Was king of the underground But I still rap like I'm on my Pharoahe Monch grind So I crunch rhymes, but sometimes when you combine Appeal with the skin color of mine You get too big and here they come tryin' To censor you like that one line I said on I'm Back from The Mathers LP 1 when I Tried to say I'll take seven kids from Columbine Put 'em all in a line, add an AK-47, a revolver and a .9 See if I get away with it now that I ain't as big as I was, but I'm Morphin' into an immortal, comin' through the portal You're stuck in a time warp from 2004 though And I don't know what the fuck that you rhyme for You're pointless as Rapunzel with fuckin' cornrow  You write normal? Fuck being normal! And I just bought a new raygun from the future Just to come and shoot ya, like when Fabolous made Ray J mad 'Cause Fab said he looked like a fag at Mayweather's pad Singin' to a man while he played piano Man, oh man, that was a 24-7 special on the cable channel So Ray J went straight to the radio station The very next day, Hey Fab, I'ma kill you! Lyrics comin' at you at supersonic speed (J.J. Fad) Uh, summa-lumma, dooma-lumma, you assumin' I'm a human What I gotta do to get it through to you I'm superhuman? Innovative and I'm made of rubber so that anything You say is ricochetin' off of me, and it'll glue to you and I'm devastating, more than ever demonstrating How to give a motherfuckin' audience a feeling like it's levitating Never fading, and I know the haters are forever waiting For the day that they can say I fell off, they'll be celebrating 'Cause I know the way to get 'em motivated I make elevating music, you make elevator music Oh, he's too mainstream Well, that's what they do when they get jealous, they confuse it It's not hip-hop, it's pop,  'cause I found a hella way to fuse it With rock, shock rap with Doc Throw on Lose Yourself and make 'em lose it I don't know how to make songs like that I don't know what words to use Let me know when it occurs to you While I'm rippin' any one of these verses that versus you It's curtains, I'm inadvertently hurtin' you How many verses I gotta murder to Prove that if you were half as nice, your songs you could sacrifice virgins too? Ugh, school flunky, pill junkie But look at the accolades these skills brung me Full of myself, but still hungry I bully myself 'cause I make me do what I put my mind to And I'm a million leagues above you Ill when I speak in tongues, but it's still tongue-in-cheek, fuck you I'm drunk, so, Satan, take the fucking wheel I'ma sleep in the front seat Bumpin' Heavy D and the Boyz, still Chunky but Funky But in my head, there's something I can feel tugging and struggling Angels fight with devils and here's what they want from me They're askin' me to eliminate some of the women hate But if you take into consideration the bitter hatred I have, then you may be a little patient And more sympathetic to the situation And understand the discrimination But fuck it, life's handin' you lemons? Make lemonade then! But if I can't batter the women How the fuck am I supposed to bake them a cake then? Don't mistake him for Satan; it's a fatal mistake If you think I need to be overseas and take a vacation To trip a broad, and make her fall on her face and Don't be a retard, be a king? Think not Why be a king when you can be a god?");
	
	ss[11].setSongName("Without-Me");
	ss[11].setArtistName("Eminem");
	ss[11].setGenre("Hip hop");
	ss[11].setReleaseDate("15/05/2002");
	ss[11].setLyrics("Obie Trice, real name no gimmicks Two trailer park girls go round the outside Round the outside, round the outside Two trailer park girls go round the outside Round the outside, round the outside Guess who's back? Back again Shady's back Tell a friend Guess who's back? Guess who's back? Guess who's back? Guess who's back? Guess who's back? Guess who's back? Guess who's back? I've created a monster 'Cause nobody wants to see Marshall no more They want Shady, I'm chopped liver Well, if you want Shady, this is what I'll give ya A little bit of weed mixed with some hard liquor Some vodka that'll jump start my heart quicker Than a shock when I get shocked at the hospital By the doctor when I'm not co-operating When I'm rockin' the table while he's operating You waited this long, now stop debating 'Cause I'm back, I'm on the rag and ovulating I know that you got a job, Ms. Cheney But your husband's heart problem's complicating So the FCC won't let me be Or let me be me, so let me see They try to shut me down on MTV But it feels so empty, without me So, come on and dip, bum on your lips Fuck that, cum on your lips and some on your tits And get ready, 'cause this is about to get heavy I just settled all my lawsuits, fuck you, Debbie! Now this looks like a job for me So everybody, just follow me 'Cause we need a little, controversy 'Cause it feels so empty, without me I said this looks like a job for me So everybody, just follow me 'Cause we need a little, controversy 'Cause it feels so empty, without me Little hellions, kids feelin' rebellious Embarrassed their parents still listen to Elvis They start feelin' like prisoners, helpless 'Til someone comes along on a mission and yells, Bitch A visionary, vision of scary Could start a revolution, pollutin' the airwaves A rebel, so just let me revel and bask In the fact that I got everyone kissin' my ass And it's a disaster, such a catastrophe For you to see so damn much of my ass, you asked for me? Well, I'm back, da-na-na-na-na-na-na-na-na-na Fix your bent antenna tune it in and then I'm gonna Enter in, endin' up under your skin like a splinter The center of attention, back for the winter I'm interesting, the best thing since wrestling Infesting, in your kid's ears and nesting Testing, attention, please Feel the tension, soon as someone mentions me Here's my ten cents, my two cents is free A nuisance, who sent? You sent for me? Now this looks like a job for me So everybody, just follow me 'Cause we need a little, controversy 'Cause it feels so empty, without me I said, this looks like a job for me So everybody, just follow me 'Cause we need a little, controversy 'Cause it feels so empty, without me A-tisket a-tasket, I go tit for tat with Anybody who's talkin' this shit that shit Chris Kirkpatrick, you can get your ass kicked Worse than them little Limp Bizkit bastards And Moby? You can get stomped by Obie You 36-year-old bald headed fag, blow me You don't know me, you're too old, let go It's over, nobody listen to techno Now let's go, just gimme the signal I'll be there with a whole list full of new insults I been dope, suspenseful with a pencil Ever since Prince turned himself into a symbol But sometimes the shit just seems Everybody only wants to discuss me So this must mean I'm disgusting But it's just me, I'm just obscene No, I'm not the first king of controversy I am the worst thing since Elvis Presley To do Black music so selfishly And used it to get myself wealthy (hey) There's a concept that works 20 million other white rappers emerge But no matter how many fish in the sea It'll be so empty, without me Now this looks like a job for me So everybody, just follow me 'Cause we need a little, controversy 'Cause it feels so empty without me I said this looks like a job for me So everybody, just follow me 'Cause we need a little, controversy 'Cause it feels so empty without me Kids!");
	
	ss[12].setSongName("Lucky-You");
	ss[12].setArtistName("Eminem");
	ss[12].setGenre("Hip hop");
	ss[12].setReleaseDate("30/11/2018");
	ss[12].setLyrics("Whoa, Joyner, Joyner, yeah, yeah, yeah Yeah, I done did a lot of things in my day, I admit it I don't take back what I say, if I said it, then I meant it All my life I want a Grammy, but I'll prolly never get it I ain't never had no trophy or no motherfuckin' ribbon (yeah, yeah, yeah) Fuck the system, I'm that nigga, bend the law, cut the rules I'm about to risk it all, I ain't got too much to lose (yeah, yeah, yeah, yeah) Y'all been eatin' long enough, it's my turn to cut the food (yeah) Pass the plate (yeah), where my drink (hol' up)? This my day (yeah, yeah), lucky you, fuck you too, woo! Y'all gotta move, y'all gotta move, y'all gotta move Give me some room (woo!), give me some room (hey!), give me the juice Hop out the coupe, hop out the coupe, hop out and shoot Y'all gotta move (boom, bap), y'all gotta move (woo!), give me the juice Back on my bullshit, my back to the wall Turn my back on you, all of you finished (bap, bop, bop) Back to these bullets, it's back to the job Pull my MAC out and all of you runnin' (yeah, yeah, yeah) Back on my hood shit, it's back to the pushin' These packs and I'm actually pumpin' Can't fuck with you rappers, you practically suckin' (yuh) You might'a went platinum, but that don't mean nothin' I'm actually buzzin' this time Straight out the kitchen, I told 'em the oven is mine I do not fuck with you guys (woo!) If I don't kill you, just know you gon' suffer this time (yeah!) I ain't no gangster, but I got some bangers Some chains and some blades and a couple of knives Choppers and jammies, a partridge, a pear tree My Twelve Days of Christmas was nothin' but lies (I) Run at you hard like a sumo (sumo) They say I talk like a chulo (chulo!) I live on Mars, I'm not Bruno (woo!) Bitch, I'm a dog, call me Cujo (rah) You play your cards, I reverse on you all And I might just draw four like a Uno (bup) Cállate boca mejor, maricón Little puto, and all of you culo (Joyner) They've invented a level up in the ghetto to get old Lookin' for somethin' I prolly can never find now (yeah, yeah) Shit get relevant 'til all the beef die down (yeah) In truth, a nigga just really want me tied down (bop, bop) I've been alone and I never needed nobody Just only me and my shawty, I'll tell these niggas to lie down Keep all the money, I never wanted the lifestyle I just pray to God that my son'll be alright now (woo! Woo!) I said ain't no love for the other side Or anyone who ever want smoke (Joyner) When I die, I'm goin' out as the underdog who never lost hope (yeah) You in the wrong cab, down the wrong path Nigga, wrong way, wrong road (woo! Woo!) Snakes in the grass tryna slither fast I just bought a fuckin' lawn mower (vroom!) I done said a lotta things in my day, I admit it This is payback in a way (yeah), I regret it that I did it I done won a couple Grammys, but I sold my soul to get 'em (ah) Wasn't in it for the trophies (nah), just the fuckin' recognition Fuck's the difference? I'm that cracker, bend the law, fuck the rule Man, I used to risk it all, now I got too much to lose I've been eatin' long enough, man, my stomach should be full I just ate, licked the plate, my buffet, lucky me, fuck you think? (Woo!) I got a couple of mansions Still, I don't have any manners You got a couple of ghostwriters But to these kids, it don't actually matter They're askin' me, What the fuck happened to hip-hop? I said, I don't have any answers 'Cause I took an L when I dropped my last album It hurt me like hell, but I'm back on these rappers (yeah) And actually comin' from humble beginnings I'm somewhat uncomfortable winning I wish I could say, What a wonderful feeling! We're on the upswing like we're punchin' the ceiling! But nothin' is feeling like anyone has any fuckin' ability To even stick to a subject, it's killin' me The inability to pen humility Ha-ta-ta, ba-ta-ta, why don't we make a bunch of Fuckin' songs about nothin' and mumble 'em? Fuck it, I'm goin' for the jugular Shit is a circus, you clowns that are comin' up Don't give an ounce of a motherfuck About the ones that were here before you that made rap (yeah) Let's recap, way back, MC's that (what?) Wreak havoc on tape decks (woo) ADAT's, where the G Raps and Kanes at? We need 3 Stacks ASAP and bring Masta Ace back 'Cause half of these rappers have brain damage All the lean rappin', face tats, syruped out like tree sap I don't hate trap (nah), and I don't wanna seem mad But in fact (yeah), where the old me at? The same cat That would take that feedback and aim back, I need that But I think it's inevitable they know what button to press Or what lever to pull to give me to snap though (lil' bitch) And if I pay it attention, I'm prob'ly makin' it bigger But you've been takin' ya dicks, and I'm fuckin' back, ho (get it?) On the brink, any minute got me thinkin' of finishin' Everything with acetaminophen and reapin' the benefits I'm asleep at the wheel again, as I begin to thinkin' about An evil intent of another beat I'ma kill again 'Cause even if I gotta end up eating a pill again Even ketamine or methamphetamine with the minithin It better be at least 70 or 300 milligram And I might as well 'cause I'ma end up bein' a villain again Levels to this shit, I got an elevator You could never say to me, I'm not a fuckin' record breaker (yeah) I sound like a broken record every time I break a record Nobody could ever take away the legacy I made, I never cater Motherfucker, now I got a right to be this way I got spite inside my DNA (yeah) But I roll 'til the wheels fall off, I'm working tirelessly, ayy It's the moment y'all been waitin' for like California Wishin' rain to pour in that drought, y'all Been prayin' for my downfall (yeah) From the 8 Mile to the Southpaw Still the same Marshall, that outlaw That they say as a writer might've fell off I'm back on that bull like the cowboy So y'all gotta move, yeah, y'all gotta move, yeah, y'all gotta move Give me some room (woo!), give me some room (hey!), give me the juice Hop out the coupe (Joyner!), hop out the coupe (Joyner!), hop out and shoot Y'all gotta move (boom, bap), y'all gotta move (woo!), give me the juice");
	
	ss[13].setSongName("Billie-Jean");
	ss[13].setArtistName("Prznt");
	ss[13].setGenre("Hip hop");
	ss[13].setReleaseDate("17/01/2020");
	ss[13].setLyrics("Bitches ain't the same now that I'm riding so clean Picking up the pot I drop the top it's so mean Landed in la I'm back tonight a new scene Love to say they love me but they love the new me Take away they mask off what you really feel like I was in the back dawg, shit didn't really feel right Had to be the boss make my niggas move the deal like How you pushing work but you with ya mama still like Shorty tryna lie the kid ain't mine at all Bitches call me daddy but thats bout it dawg No you ain't my lover bitch you just a fraud They gon' hate me up but love to watch me fall Ima k9 yeah ima dog Diamonds on me they ain't got no flaws This time last year I ain't had a damn thing but I got it popping now I'm the boss I got these racks On my Jeans She loves me Billie Jean Vvs's on me clean I make all these bitches scream I got these racks On my Jeans She loves me Billie Jean Vvs's on me clean I make all these bitches scream I used to love this shit a lot now I love it more The riding round the city part is what I do it for A lot of niggas hated but I gotta just ignore They flaking like some ashes burn them out into the floor Watch ya back around these folks naw Hold on Say you wanna go nah oh nah Flying round the globe awe so far Got my shorty thinking I been fucking on these thots Sorry I been lying but a nigga having fun I'm just getting paid getting laid getting freaked on Getting sleeped I mean slept Getting deep throat Watch who come around cause I got niggas acting sneak dawg I got these racks On my Jeans She loves me Billie Jean Vvs's on me clean I make all these bitches scream I got these racks On my Jeans She loves me Billie Jean Vvs's on me clean I make all these bitches scream");
	
	ss[14].setSongName("CHECKLIST");
	ss[14].setArtistName("Prznt");
	ss[14].setGenre("Hip hop");
	ss[14].setReleaseDate("19/01/2020");
	ss[14].setLyrics("Keep the talking I don't rest bitch, Ima mark it on ma checklist Ima roll it off in a Benz bitch try not To catch I be the man and you helpless uhhh Yeah, she fucking with me cuz she can I want them hundreds in grams Fuck up the scam to leave me the digits I ran yeah aye Oh, yeah, oh, okay, yeah 47 shots Keep the talking I don't rest bitch, Ima mark it on ma checklist Ima roll it off in a Benz bitch try not To catch I be the man and you helpless uhhh Yeah, she fucking with me cuz she can I want them hundreds in grams Fuck up the scam to leave me the digits I ran yeah aye Keep the talking I don't rest bitch, Ima mark it on ma checklist Ima roll it off in a Benz bitch try not To catch I be the man and you helpless uhhh Yeah, she fucking with me cuz she can I want them hundreds in grams Fuck up the scam to leave me the digits I ran yeah aye I just need a lighter, Ima roll that fye up She said she ain't riding if we sliding out that fire truck Ima stay away from her Young niggas ain't good with birds, that sack moved get out my turn Ima fuck her sister first, she said I done denied I said ohhh whyy? She said she don't fly with guys no ride or die But she get piped and leave the sight like damnn No motion this my plan I ran the check now who up next wait oh shit this my land yeah ayy Keep the talking I don't rest bitch, Ima mark it on ma checklist Ima roll it off in a Benz bitch try not To catch I be the man and you helpless uhhh Yeah, she fucking with me cuz she can I want them hundreds in grams Fuck up the scam to leave me the digits I ran yeah aye Keep the talking I don't rest bitch, Ima mark it on ma checklist Ima roll it off in a Benz bitch try not To catch I be the man and you helpless uhhh Yeah, she fucking with me cuz she can I want them hundreds in grams Fuck up the scam to leave me the digits I ran yeah aye I'm so high but I feel so low I be fucking bitches they be thinking they'll blow I don't really wanna count the digits no more They be talkin bout my niggas like my niggas don't go I got em I got em I let em go down Fuck what you thought I'm the greatest around Drop that bitch off in her wedding ring, gown I told you I'll fuck you and leave you right now Yeah ain't my fault no, that I just ball woah I hit it off the wall tho, ain't shopping at the mall no I just wanna hit it from the back one time Swear to god you better never call my line I got all my bitches in a check like signs And I'm tryna make a mill off every rap or rhyme");
	
	ss[15].setSongName("Highlight-Of-The-Night");
	ss[15].setArtistName("Prznt");
	ss[15].setGenre("Electronic");
	ss[15].setReleaseDate("11/03/2021");
	ss[15].setLyrics("See the highlight of the night Say's she living right I've spent long the time, I see the look in both her eyes With the highlight for the ride Keep it on my side I wrote with dem haters she like curly let it fly See the highlight of the night With the highlight for the ride See the highlight of the night See the highlight for the ride Why you around my corner I behave like a bro no? Turn a goody bitch to a stoner Turn a couple cats into a honer They been run on em but don't act by it I never act now for anybody Only broth?rs run me No false siding, no tools at it we alright Tell me that you go go Sliding on a boat That shawty's a good girl, but I turn into a hore She turn a night into a fantasy And I'ma See the highlight of the night Say's she living right I've spent long the time, I see the look in both her eyes With the highlight for the ride Keep it on my side I wrote with dem haters she like curly let it fly See the highlight of the night With the highlight for the ride See the highlight of the night See the highlight for the ride Slide outta the way Pull up in a ray I stay away from no pussy then no face All these motherfuckers say they wanna hate Cause they ain't got nothing they got no food up on the plate They say coup, I'm in a coup Say she gon' move Nobody wanna pour Say she do She know that I been on I'm sliding you");
	
	ss[16].setSongName("ALONE");
	ss[16].setArtistName("Prznt");
	ss[16].setGenre("Nigerian Alté");
	ss[16].setReleaseDate("26/07/2018");
	ss[16].setLyrics("Yeah Yeah I been all alone They just started coming after me when i got on Shawty think I'm flying cuz I got lenciagas on All my bitches know I do 'em right and never wrong Yeah Yeah Yeah I can't go inside, I can't even Hide Yeah, no one hit my line no you cannot slid I was with them bands, always been the man Yeah, said you understand but you don't understand How can I add it up I got too much dough in my pocket let it up These niggas be federal They act like ya homie they leave and go tell it all Don't fit in my schedule I fucked all these thotties Up packing the centrefolds You smoking on general Was way of the molly that shawty look terrible Just let the picture roll, too much sauce invincible Trap out side the kitchen door Move out cold like water coats Threesome with some tinder hoes LA bitches do the most I'm just bad at losing and They mad i used that finger roll Tap in the racks in the money I'm gone I got yo message I'm not going home I won't hit ya line but I swear i want some dome I fucked you all the time now i do not hit ya phone I been all alone They just started coming after me when i got on Shawty think I'm flying cuz I got lenciagas on All my bitches know I do 'em right and never wrong Yeah Yeah Yeah I been all alone They just started coming after me when i got on Shawty think I'm flying cuz I got lenciagas on All my bitches know I do 'em right and never wrong Yeah Yeah Yeah I wanna know, if she wanna roll I got my dough, I'm ready to go Let me show you, it's something I like I don't sip on mary jane I mix the purple W. the Sprite Then I go, Then i do my thang Then I hit the road never change Ima stay the the same I been on way, never know How you get the gold, I swear Insane might unload I just hit the fold, you gon feel the pain, yeah");
	
	ss[17].setSongName("Laudy-Daudy");
	ss[17].setArtistName("Prznt");
	ss[17].setGenre("Hip hop");
	ss[17].setReleaseDate("30/07/2018");
	ss[17].setLyrics("Yeah, yeah, yeah I ain't with the Laudy Daudy My shorty, shorty, coming for bodies, aye I don't got no type of problems But I could solve 'em, try not to complicate it Bitch, I'm a dog, just face it All of you hoes, just basic I know they hating on me Better than ever so how can you hate this I ain't with the Laudy Daudy My shorty, shorty, coming for bodies, aye I don't got no type of problems But I could solve 'em, try not to complicate it Bitch, I'm a dog, just face it All of you hoes, just basic I know they hating on me Better than ever so how can you hate this And, I ain't with the Laudy Daudy I just fuck and leave my kids all in these bitches body I just wanna make it big and tell 'em that I'm sorry Tell 'em that I never ment it but I love to party And I had to get it up 'cause I love these hoes Winning I'm winning but I'm wanting more I took 'em for ransom, and ran for my bro These niggas be hating 'cause I got the gold And I'mma go get it I'm feeling so kosher I went from doing what I'm 'posed to To getting what you wanted most of Like riding in Benzes and Rovers I got your bitch riding beside me She crazy she wanna be wifey ot everything that you might need Hoes they be texting me pipe me I ain't with the Laudy Daudy My shorty, shorty, coming for bodies, aye I don't got no type of problems But I could solve 'em, try not to complicate it Bitch, I'm a dog, just face it All of you hoes, just basic I know they hating on me Better than ever so how can you hate this");
	
	ss[18].setSongName("Brooklyn-Baby");
	ss[18].setArtistName("Lana Del Rey");
	ss[18].setGenre("Electronic");
	ss[18].setReleaseDate("8/06/2014");
	ss[18].setLyrics("Ta-da-da-da-da-da-da Ta-da-da-da-da-da-da Da-da-da-da-da-da-da They say I'm too young to love you I don't know what I need They think I don't understand The freedom land of the seventies I think I'm too cool to know ya You say I'm like the ice, I freeze I'm churnin' out novels like Beat poetry on Amphetamines I say I say Well, my boyfriend's in a band He plays guitar while I sing Lou Reed I've got feathers in my hair I get down to Beat poetry And my jazz collection's rare I can play most anything I'm a Brooklyn baby I'm a Brooklyn baby Ta-da-da-da-da-da-da Ta-da-da-da-da-da-da Pa-ta-da-da-da-da They say I'm too young to love you They say I'm too dumb to see They judge me like a picture book By the colors, like they forgot to read I think we're like fire and water I think we're like the wind and sea You're burnin' up, I'm coolin' down You're up, I'm down You're blind, I see But I'm free, ooh-ooh I'm free Well, my boyfriend's in a band He plays guitar while I sing Lou Reed I've got feathers in my hair I get down to Beat poetry And my jazz collection's rare I can play most anything I'm a Brooklyn baby I'm a Brooklyn baby I'm talking about my generation Talking about that newer nation And if you don't like it, you can beat it Beat it, baby You never liked the way I said it If you don't get it, then forget it 'Cause I don't have to fuckin' explain it And my boyfriend's in a band He plays guitar while I sing Lou Reed I've got feathers in my hair I get high on hydroponic weed And my jazz collection's rare I get down to Beat poetry I'm a Brooklyn baby I'm a Brooklyn baby Pa-da-pa-pa, pa-de-da Te-de-de, da-da-ah Ooh-ooh, woah Yeah, my boyfriend's pretty cool But he's not as cool as me 'Cause I'm a Brooklyn baby I'm a Brooklyn baby Pa-da-da-da-da-da-da Da-da-da-da-da, baby Ah-ta-da-da-da-da Da-da-da-da, baby Pa-da-da-da-da-da Pa-pa-da-pa-da, yeah Yeah, yeah");
	
	ss[19].setSongName("Young-And-Beautiful");
	ss[19].setArtistName("Lana Del Rey");
	ss[19].setGenre("Pop");
	ss[19].setReleaseDate("23/04/2013");
	ss[19].setLyrics("I've seen the world, done it all, had my cake now Diamonds, brilliant, and Bel Air now Hot summer nights, mid-July When you and I were forever wild The crazy days, city lights The way you'd play with me like a child Will you still love me when I'm no longer young and beautiful? Will you still love me when I got nothing but my aching soul? I know you will, I know you will, I know that you will Will you still love me when I'm no longer beautiful? I've seen the world, lit it up as my stage now Channeling angels in the new age now Hot summer days, rock and roll The way you'd play for me at your show And all the ways I got to know Your pretty face and electric soul Will you still love me when I'm no longer young and beautiful? Will you still love me when I got nothing but my aching soul? I know you will, I know you will, I know that you will Will you still love me when I'm no longer beautiful? Dear Lord, when I get to Heaven Please let me bring my man When he comes, tell me that you'll let him in Father, tell me if you can All that grace, all that body All that face makes me wanna party He's my sun, he makes me shine like diamonds Will you still love me when I'm no longer young and beautiful? Will you still love me when I got nothing but my aching soul? I know you will, I know you will, I know that you will Will you still love me when I'm no longer beautiful? Will you still love me when I'm no longer beautiful? Will you still love me when I'm not young and beautiful?");
	
	ss[20].setSongName("Doin-Time");
	ss[20].setArtistName("Lana Del Rey");
	ss[20].setGenre("Indie");
	ss[20].setReleaseDate("17/05/2019");
	ss[20].setLyrics("Summertime, and the livin's easy Bradley's on the microphone with Ras MG All the people in the dance will agree That we're well-qualified to represent the L.B.C Me, me and Louie, we gonna run to the party And dance to the rhythm, it gets harder Me and my girl, we got this relationship I love her so bad, but she treats me like shit On lockdown, like a penitentiary She spreads her lovin' all over And when she gets home, there's none left for me Summertime, and the livin's easy Bradley's on the microphone with Ras MG All the people in the dance will agree That we're well-qualified to represent the L.B.C Me, me and Louie, we gonna run to the party And dance to the rhythm, it gets harder (Harder, yeah, harder, yeah) Oh, take this veil from off my eyes My burning sun will, some day, rise So, what am I gonna be doin' for a while? Said, I'm gonna play with myself Show them, now, we've come off the shelf Summertime, and the livin's easy Bradley's on the microphone with Ras MG All the people in the dance will agree That we're well-qualified to represent the L.B.C Me, me and Louie, we gonna run to the party And dance to the rhythm, it gets harder (Harder, yeah, harder, yeah) Evil, I've come to tell you that she's evil, most definitely Evil, ornery, scandalous and evil, most definitely The tension, it's getting hotter I'd like to hold her head underwater (Summertime) (Ah, ah, ah) Summertime, and the livin's easy Bradley's on the microphone with Ras MG All the people in the dance will agree That we're well-qualified to represent the L.B.C Me, me and Louie, we gonna run to the party And dance to the rhythm, it gets harder");
	
	ss[21].setSongName("Summertime-Sadness");
	ss[21].setArtistName("Lana Del Rey");
	ss[21].setGenre("Indie");
	ss[21].setReleaseDate("22/06/2012");
	ss[21].setLyrics("I got my red dress on tonight Dancin' in the dark in the pale moonlight Done my hair up real big, beauty queen style High heels off, I'm feelin' alive Oh my God, I feel it in the air Telephone wires above Are sizzlin' like a snare Honey, I'm on fire, I feel it everywhere Nothin' scares me anymore Kiss me hard before you go Summertime sadness I just wanted you to know That baby, you the best I got that summertime, summertime sadness Su-su-summertime, summertime sadness Got that summertime, summertime sadness Oh, oh-oh, oh-oh, oh-oh Oh-oh, oh-oh, oh-oh, oh-oh Oh-oh, oh-oh, oh-oh, oh-oh Oh-oh, oh-oh I got that summertime I got that summertime I got that summertime, I got that summertime I got that summertime, summertime sadness I got that summertime, I got that summertime I got that summertime, summertime sadness I'm feelin' electric tonight Cruisin' down the coast, goin' 'bout 99 Got my bad baby by my heavenly side I know if I go, I'll die happy tonight Oh my God, I feel it in the air Telephone wires above Are sizzlin' like a snare Honey, I'm on fire, I feel it everywhere Nothin' scares me anymore Kiss me hard before you go Summertime sadness I just wanted you to know That baby, you the best I got that summertime, summertime sadness Su-su-summertime, summertime sadness Got that summertime, summertime sadness Oh, oh-oh, oh-oh, oh-oh Oh-oh, oh-oh, oh-oh, oh-oh Oh-oh, oh-oh, oh-oh, oh-oh Oh-oh, oh-oh I got that summertime I got that summertime I got that summertime, I got that summertime Summertime sadness I got that summertime, I got that summertime I got that summertime, I got that summertime Summertime sadness I got that summertime, I got that summertime Summertime sadness I got that summertime, I got that summertime I got that summertime, I got that summertime Summertime sadness");
	
	ss[22].setSongName("Lust-For-Life");
	ss[22].setArtistName("Lana Del Rey");
	ss[22].setGenre("Pop");
	ss[22].setReleaseDate("21/07/2017");
	ss[22].setLyrics("climb up the H of the Hollywood sign, yeah In these stolen moments The world is mine (doo-wop, doo-wop) There's nobody here, just us together (shoo-roo, shoo-roo) Keepin' me hot like July forever 'Cause we're the masters of our own fate We're the captains of our own souls There's no way for us to come away 'Cause boy we're gold, boy we're gold And I was like Take off, take off Take off all your clothes Take off, take off Take off all your clothes Take off, take off Take off all of your clothes They say only the good die young That just ain't right 'Cause we're having too much fun Too much fun tonight, yeah And a lust for life, and a lust for life And a lust for life, and a lust for life Keeps us alive, keeps us alive Keeps us alive, keeps us alive And a lust for life, and a lust for life And a lust for life, and a lust for life Keeps us alive, keeps us alive Keeps us alive, keeps us alive Then, we dance on the H of the Hollywood sign, yeah 'Til we run out of breath, gotta dance 'til we die (doo-wop, doo-wop) My boyfriend's back And he's cooler than ever (shoo-roo, shoo-roo) There's no more night, blue skies forever 'Cause we're the masters of our own fate We're the captains of our own souls So there's no need for us to hesitate We're all alone, let's take control And I was like Take off, take off Take off all your clothes Take off, take off Take off all your clothes Take off, take off Take off all of your clothes They say only the good die young That just ain't right 'Cause we're having too much fun Too much fun tonight, yeah And a lust for life, and a lust for life And a lust for life, and a lust for life Keeps us alive, keeps us alive Keeps us alive, keeps us alive And a lust for life, and a lust for life And a lust for life, and a lust for life Keeps us alive, keeps us alive Keeps us alive, keeps us alive (oh) My boyfriend's back And he's cooler than ever There's no more night, blue skies forever I told you twice in our love letter There's no stopping now, green lights forever And I was like Take off, take off Take off all your clothes Take off, take off Take off all your clothes Take off, take off Take off all of your clothes And a lust for life, and a lust for life And a lust for life, and a lust for life Keeps us alive, keeps us alive Keeps us alive, keeps us alive And a lust for life, and a lust for life And a lust for life, and a lust for life Keeps us alive, keeps us alive Keeps us alive, keeps us alive (oh-ooh)");
	
	ss[23].setSongName("After-Hours");
	ss[23].setArtistName("The Weekend");
	ss[23].setGenre("Indie");
	ss[23].setReleaseDate("20/03/2020");
	ss[23].setLyrics("Thought I almost died in my dream again (baby, almost died) Fightin' for my life, I couldn't breathe again I'm fallin' in too deep (oh) Without you, don't wanna sleep (fallin' in) 'Cause my heart belongs to you I'll risk it all for you I want you next to me This time, I'll never leave I wanna share babies Protection, we won't need Your body next to me Is just a memory I'm fallin' in too deep, oh Without you, I can't sleep Insomnia, don't leave, oh Talk to me, without you I can't breathe My darkest hours Girl, I felt so alone inside of this crowded room Different girls on the floor, distracting my thoughts of you I turned into the man I used to be, to be Put myself to sleep Just so I can get closer to you inside my dreams Didn't wanna wake up 'less you were beside me I just wanted to call you and say, and say Oh, baby, where are you now when I need you most? I'd give it all just to hold you close Sorry that I broke your heart, your heart Never comin' down, uh I was runnin' away from facin' reality, uh Wastin' all of my time on livin' my fantasies Spendin' money to compensate, compensate 'Cause I want you baby I'll be livin' in Heaven when I'm inside of you It was definitely a blessing wakin' beside you I'll never let you down again, again Oh, baby, where are you now when I need you most? I'd give it all just to hold you close Sorry that I broke your heart, your heart I said, baby, I'll treat you better than I did before I'll hold you down and not let you go This time I won't break your heart, your heart, yeah I know it's all my fault Made you put down your guard I know I made you fall Then said you were wrong for me I lied to you, I lied to you, I lied to you (to you) Can't hide the truth, I stayed with her in spite of you You did some things that you regret, still ride for you 'Cause this house is not a home Without my baby, where are you now when I need you most? I gave it all just to hold you close Sorry that I broke your heart, your heart And I said, baby, I'll treat you better than I did before I'll hold you down and not let you go This time I won't break your heart, your heart, no");
	
	ss[24].setSongName("The-Hills");
	ss[24].setArtistName("The Weekend");
	ss[24].setGenre("Electronic");
	ss[24].setReleaseDate("27/05/2015");
	ss[24].setLyrics("Yeah Yeah Yeah Your man on the road, he doin' promo You said, Keep our business on the low-low I'm just tryna get you out the friend zone 'Cause you look even better than the photos I can't find your house, send me the info Drivin' through the gated residential Found out I was comin', sent your friends home Keep on tryna hide it, but your friends know I only call you when it's half-past five The only time that I'll be by your side I only love it when you touch me, not feel me When I'm fucked up, that's the real me When I'm fucked up, that's the real me, yeah I only call you when it's half-past five The only time I'd ever call you mine I only love it when you touch me, not feel me When I'm fucked up, that's the real me When I'm fucked up, that's the real me, babe I'ma let you know and keep it simple Tryna keep it up don't seem so simple I just fucked two bitches 'fore I saw you And you gon' have to do it at my tempo Always tryna send me off to rehab Drugs started feelin' like it's decaf I'm just tryna live life for the moment And all these motherfuckers want a relapse I only call you when it's half-past five The only time that I'll be by your side I only love it when you touch me, not feel me When I'm fucked up, that's the real me When I'm fucked up, that's the real me, yeah I only call you when it's half-past five The only time I'd ever call you mine I only love it when you touch me, not feel me When I'm fucked up, that's the real me When I'm fucked up, that's the real me, babe Hills have eyes, the hills have eyes Who are you to judge? Who are you to judge? Hide your lies, girl, hide your lies Only you to trust, only you I only call you when it's half-past five The only time that I'll be by your side I only love it when you touch me, not feel me When I'm fucked up, that's the real me When I'm fucked up, that's the real me, yeah I only call you when it's half-past five The only time I'd ever call you mine I only love it when you touch me, not feel me When I'm fucked up, that's the real me When I'm fucked up, that's the real me, babe");
	
	ss[25].setSongName("Reminder");
	ss[25].setArtistName("The Weekend");
	ss[25].setGenre("Pop");
	ss[25].setReleaseDate("9/05/2017");
	ss[25].setLyrics("Record man play my song on the radio You too busy trying to find that blue-eyed soul I let my black hair grow and my weed smoke And I swear too much on the regular We gon' let them hits fly, we gon' let it go If it ain't XO then it gotta go I just won a new award for a kids show Talking 'bout a face numbing off a bag of blow I'm like, goddamn, bitch, I am not a Teen Choice Goddamn, bitch, I am not a bleach boy Whip game, make a nigga understand though Got that Hannibal, Silence of the Lambo Hit the gas so hard make it rotate All my niggas blew up like a propane All these R&B niggas be so lame Got a sweet Asian chick, she go low mane (low mane, low mane) You know me, know me You know, man, know, man, know, man You know me, know me, know me Every time you try to forget who I am I'll be right there to remind you again You know me, know me (pow, pow) You know me, know me Said I'm just tryna swim in something wetter than the ocean Faded off a double cup, I'm mixing up the potion All I wanna do is make that money and make dope shit It just seem like niggas tryna sound like all my old shit Everybody knows it, all these niggas know me Platinum off a mixtape, sipping on that codeine Pour it in my trophies, roll until my nose bleed I'ma keep on singing while I'm burning up that OG All my niggas get it, they make money all alone Rock a chain around they neck, making sure I'm getting home When I travel 'round the globe, make a couple mil' a show And I come back to my city, I fuck every girl I know Used to walk around with a slouch, had a mattress on the floor Now my shit straight, eating all day, tryna lose weight That good sex, we'll sweat it out Hotel bed springs, we'll wear it out I ain't gotta tell you 'cause you know me You know me, know me You know, man, know, man, know, man You know me, know me, know me Every time you try to forget who I am I'll be right there to remind you again You know me, know me (pow, pow) You know me, know me (know me, know me) Why don't you shake some, shake somethin' for the Don? Don't you break nothin', break nothin', baby girl Won't you work some, work somethin' for the Don? Don't you hurt nothin', hurt nothin', big girl Won't you shake some, shake somethin' for the Don? Don't you break nothin', break nothin', baby girl Won't you work some, work somethin' for the Don? Don't you hurt nothin', hurt nothin' 'Cause you know me, they know me You're a no-man, yeah, you know, man Oh-oh-oh, na-na-na-na-na Oh-oh-oh, na-na-na-na-na Oh-oh-oh, na-na-na-na-na Oh-oh-oh, na-na-na-na-na");
	
	ss[26].setSongName("Starboy");
	ss[26].setArtistName("The Weekend");
	ss[26].setGenre("Hip hop");
	ss[26].setReleaseDate("25/11/2015");
	ss[26].setLyrics("I'm tryna put you in the worst mood, ah P1 cleaner than your church shoes, ah Milli' point two just to hurt you, ah All red Lamb' just to tease you, ah None of these toys on lease too, ah Made your whole year in a week too, yeah Main bitch outta your league too, ah Side bitch out of your league too, ah House so empty, need a centerpiece 20 racks a table, cut from ebony Cut that ivory into skinny pieces Then she clean it with her face, man, I love my baby, ah You talking money, need a hearing aid You talking 'bout me, I don't see the shade Switch up my style, I take any lane I switch up my cup, I kill any pain Look what you've done I'm a motherfucking starboy Look what you've done I'm a motherfucking starboy Every day a nigga try to test me, ah Every day a nigga try to end me, ah Pull off in that Roadster SV, ah Pockets overweight, getting hefty, ah Coming for the king, that's a far cry, I I come alive in the fall time, I The competition, I don't really listen I'm in the blue Mulsanne bumping New Edition House so empty, need a centerpiece 20 racks a table, cut from ebony Cut that ivory into skinny pieces Then she clean it with her face, man, I love my baby, ah You talking money, need a hearing aid You talking 'bout me, I don't see the shade Switch up my style, I take any lane I switch up my cup, I kill any pain Look what you've done I'm a motherfucking starboy Look what you've done I'm a motherfucking starboy Let a nigga brag Pitt Legend of the fall, took the year like a bandit Bought mama a crib and a brand-new wagon Now she hit the grocery shop looking lavish Star Trek roof in that Wraith of Khan Girls get loose when they hear this song A hundred on the dash, get me close to God We don't pray for love, we just pray for cars House so empty, need a centerpiece 20 racks a table, cut from ebony Cut that ivory into skinny pieces Then she clean it with her face, man, I love my baby, ah You talking money, need a hearing aid You talking 'bout me, I don't see the shade Switch up my style, I take any lane I switch up my cup, I kill any pain Look what you've done I'm a motherfucking starboy Look what you've done I'm a motherfucking starboy Look what you've done I'm a motherfucking starboy Look what you've done I'm a motherfucking starboy");
	
	ss[27].setSongName("I-Was-Never-There");
	ss[27].setArtistName("The Weekend");
	ss[27].setGenre("Rock");
	ss[27].setReleaseDate("30/03/2018");
	ss[27].setLyrics("What makes a grown man wanna cry? (Cry, cry, cry, cry) What makes him wanna take his life? Ah, oh (ah) His happiness is never real (Real, real, real, real) And mindless sex is how he feels, ooh, he feels When it's time, when it's time, when it's time It won't matter (it don't matter) It won't matter (matter) When it's time, when it's time, when it's time (time, it's time, babe) It won't matter (it won't matter, babe) It won't matter (yeah) It was like I was never there (It was like I was never there) It was like he was gone in thin air (no) When it's time, when it's time, when it's time (oh, baby) It won't matter (it won't matter, babe) it won't matter When it's time, when it's time, when it's time It won't matter, it won't matter When it's time, when it's time, when it's time It won't matter, it won't matter It was like I was never there It was like he was gone in thin air When it's time, when it's time, when it's time It won't matter, it won't matter Ooh, and now I know what love is And I know it ain't you for sure You'd rather something toxic So, I'll poison myself again, again 'Til I feel nothing In my soul (in my soul) I'm on the edge of something breakin' I feel my mind is slowly fadin' If I keep goin', I won't make it If I keep goin', I won't make it And it's all because of you It's all because of you It's all because of you It's all because of you Whoa, whoa (when it's time, when it's time, when it's time) Don't you, baby, hey (it won't matter, it won't matter) It won't matter, baby (when it's time, when it's time, when it's time) Don't you know? (it won't matter) Don't you know? (it won't matter) Ooh, oh, hey (When it's time, when it's time, when it's time) (It won't matter, whoa-oh)");
	
	ss[28].setSongName("Far-Alone");
	ss[28].setArtistName("G-Eazy");
	ss[28].setGenre("Hip hop");
	ss[28].setReleaseDate("14/03/2014");
	ss[28].setLyrics("Yeah, yeah, yeah Blue jeans, Air ones and a white tee '06, hangin' out the window like, yee Hyphy on one, off a bottle might be, my tree Smokin' Agent Orange, Hi-C Back when me and Marty was recordin' at my mom's Most of y'all were chasin' around bops Always in the lab, only hoping that my job Never would be based around mops now I'm on Yeah, she know, love me 'cause my ego Girls and the drugs always follow us where we go Ayy, where the Bay at? Shouts out to Jay Ant Lookin' for the party girls, let me know where they at Skinny rich girls always askin' where the yay at Throw a house party like cool, where you stay at? Turn upside down, let her tweak on the wall Took her to the bathroom and did work in the stall, yeah They used to tell me, I couldn't go too far alone (oh, far alone, alone) They used to always say I couldn't go too far alone (oh, far alone) But now I'm here, bitch, ooh (but now I'm here, bitch, ooh) But now I'm here, bitch, ooh (but now I'm here, bitch, ooh) (G-Eazy, let E-Feezy tell his story) But now I'm here, bitch Uh, it ain't funny what I've been through (uh-uh) Your enemy can be some kin to you (that's right) I started off hella broke (broke) Hung around people that's older than me, took notes (notes) Mama worked three jobs on the weekends Used to help her wash the walls at Mare Island (Mare Island?) In Vallejo naval houses Havin' a roof over my head was my allowance (for real) The oldest of four, young adults (adults) Surrounded by grief, big dreams and hope They hated and they doubt How did you take it? Took it with a grain of salt I wanted it badly, they couldn't stop me, indie Erry label wanted to sign me (who you grew up on?) Grew up on Short and Freddie B (Who else?) Magic Mike and Calvin T They used to tell me, I couldn't go too far alone (oh, far alone, alone) They used to always say I couldn't go too far alone (oh, far alone) But now I'm here, bitch, ooh (but now I'm here, bitch, ooh) But now I'm here, bitch, ooh (but now I'm here, bitch, ooh) Yeah But now I'm here, bitch From the BART train to a tour bus Still the same game except I'm pulling more sluts More butts, more bucks, never giving more fucks Did it my way, I'm never taking short cuts Raised in that town like fool, who put you upon, huh? E-40, Mac Dre is who I grew up on I been selling game got you if you need a coupon You can check my resume, see every beat I threw up on Smoking on grapes, rollin' up Swishers, no papes Back of the Ghost, closed drapes I'm a boss tycoon Girls in the crowd all swoon Super high, I'm off to the moon And I vanished with your girl, then I took her to my room She wants me to slay, okay, that means doom Boom, and it's to be expected Knew this would happen as soon as she texted They used to tell me, I couldn't go too far alone (oh, far alone, alone) They used to always say I couldn't go too far alone (oh, far alone) But now I'm here, bitch, ooh (but now I'm here, bitch, ooh) But now I'm here, bitch, ooh (but now I'm here, bitch, ooh)");
	
	ss[29].setSongName("Hate-The-Way");
	ss[29].setArtistName("G-Eazy");
	ss[29].setGenre("Pop");
	ss[29].setReleaseDate("16/10/2020");
	ss[29].setLyrics("Yeah I hate the way, the way I always miss you Yeah, I know I'm crazy but you're sick too Even after everything we been through Thought I was the one with all the issues And every time I leave, it's too long And every time I leave, it's all wrong (you know) I hate the way, the way I always miss you (ayy) (I hate the way, the way I always miss you) yeah Made a promise to myself, a promise I should stick to Talkin' to myself, I said I promised I would quit you I've been tryna let go but it's powerful, it grips you First you think you got control until I see you, can't resist you Know I got my issues, some I won't admit to No-one's got the answers, everybody wants to fix you Got this Magic 8-Ball, but I ain't got no crystal Just don't fall in Courtney Love And don't go Cobain with no pistol (no pistol) It don't take a psychic or a scientist to know that Then why the f- the minute I see you, I always go back? The definition of insanity is... yeah, I know that I had a hundred chances to move on, I always... I always blow that, yeah I can't seem to find out what's the issue See your face on my Explore and then I miss you Yeah, I said I was finished f- ing wit' you I said I hate the fucking way I always... I hate the way, the way I always miss you (miss you) Yeah, I know I'm crazy but you're sick too Even after everything we been through Thought I was the one with all the issues And every time I leave, it's too long And every time I leave, it's all wrong I hate the way, the way I always miss you (yeah) (I hate the way, the way I always miss you) ayy, yeah (yeah-yeah) Lie to myself every time I say that I'm done with you Every day without you passes slower than one wit' you Two days pass, it's feelin' like a week, this shit is stressful I swear, all these helpin' hands ain't even helpful Wishing I was closer to you, wish you wasn't distant Wishing I was wit' you, still wish this shit was different Wishing we could travel back in time and we could switch it All this pain, wishin' it was something that could fix it Medicate myself, different substances, I mix it Set my limits, try to draw the line and then she sniffs it Never lied, I give you my word and then you twist it Fights outside the club, I think the paparazzi... Think the paparazzi flicked it, yeah Still can't seem to find out what's the issue Hate the way you talkin' when you with your friends too, yeah They don't know about the shit we've been through I said I hate the fucking way I always... I hate the way, the way I always miss you (miss you) Yeah, I know I'm crazy but you're sick too Even after everything we been through Thought I was the one with all the issues And every time I leave, it's too long And every time I leave, it's all wrong I hate the way, the way I always miss you (I hate the way, the way I always miss you) I hate the way, the way I always miss you");
	
	ss[30].setSongName("No-Limit");
	ss[30].setArtistName("G-Eazy");
	ss[30].setGenre("Hip hop");
	ss[30].setReleaseDate("08/09/2017");
	ss[30].setLyrics("If I hit it one time, I'ma pipe her If I hit it two times, then I like her If I fuck three times, I'ma wife her It ain't safe for the black or the white girls It ain't safe, it ain't safe It ain't safe, it ain't safe Tell your man pipe up, nigga pipe up Hunnit bands from the safe In your face, what'd you say? (Ayy, ayy, ayy) Money, dance, turn this shit into a nightclub (Ayy, ayy, ayy) Yeah, fuck with me and get some money (Yeah, ayy) Fuck with me and get some money (Ayy, yeah) Fuck with me and get some money (Ayy, yeah) Fuck with G and get some money No limit, I'm a fucking soldier, ayy Always lit, yeah, I'm never sober It's been three days in a row, your bitch coming over Told that bitch to kick rock, she act like it's a boulder, ay 'Rari, shopping, let me, cop it Always, poppin', hella, poppin' She's a bopper, homie, hoppin' Ain't no, stopping, album, dropping Got the city on fire Bitch lying on me like she tired I might have to fuck around and call Kamaiyah Hoe stirring up the pot, jambalaya (Young Gerald) If I hit it one time, I'ma pipe her If I hit it two times, then I like her If I fuck three times, I'ma wife her It ain't safe for the black or the white girls It ain't safe, it ain't safe It ain't safe, it ain't safe Tell your man pipe up, nigga pipe up Hunnit bands from the safe In your face, what'd you say? (Ayy, ayy, ayy) Money, dance, turn this shit into a nightclub (Ayy, ayy, ayy) Yeah, fuck him then I get some money, yeah Fuck him then I get some money, yeah Fuck him then I get some money, yeah Fuck him then I get some money I need tongue, I need face Give me brain, concentrate Apple phone, Prada case Kill a weave, rock a lace Fuck the Moet, buy the ACE Fuck the Ghost, drive a Wraith Get some money, flood the Rollie Fuck the Rollie, Patek face My career takin' off These hoes jogging in place Swear these hoes run they mouth How these hoes out of shape? Can you stop with all the subs? Bitch I ain't Jared If you really want some smoke You can pull up, you can get it Grab a hand full of braids, make a nigga eat me out Put a white boy on Sazón I might turn G-Eazy out Keep it G from the club 'til the end, from the start You know me, Cardi B Pussy poppin' on the charts, ah, ah If I hit it one time I'ma pipe her If I hit it two times then I like her If I fuck three times I'ma wife her It ain't safe for the black or the white girls It ain't safe, it ain't safe It ain't safe, it ain't safe Tell your man pipe up, nigga pipe up Hunnit bands from the safe (Ayy, ayy, ayy) In your face, what'd you say? (Ayy, ayy, ayy) Money, dance, turn this shit into a nightclub (Ayy, ayy, ayy) Yeah, fuck with me and get some money, yeah ayy Fuck with me and get some money (Ayy, yeah) Fuck with me and get some money (Ayy, yeah) Fuck with G and get some money Yeah it ain't nice fam You could study where I'm from on my Viceland This is nothing new to me, this my life fam I can pull a million girls from my mic stand Pull one at my show 'cause I like fans Later on I got two in my night plans Man this year I got three hundred one night stands Keep a Costco pack of rubbers in my night stand Damn Daniel, back again with the, hah, Saint Laurent Ayy, they send me product, yeah it's retarded Ayy, this is free, ayy, bitch you brought it Bitch you on my dick, ayy, bitch get off it If I hit it one time I'ma pipe her If I hit it two times then I like her (I like her) If I fuck three times I'ma wife her (Wife her) It ain't safe for the black or the white girls It ain't safe, it ain't safe It ain't safe, it ain't safe Tell your man pipe up, nigga pipe up Hunnit bands from the safe (Ayy, ayy, ayy) In your face, what'd you say? (Ayy, ayy, ayy) Money, dance, turn this shit into a nightclub (Ayy, ayy, ayy) Yeah, fuck with me and get some money, yeah ayy Fuck with me and get some money (Ayy, yeah) Fuck with me and get some money (Ayy, yeah) Fuck with G and get some money");
	
	ss[31].setSongName("Me-Myself-&-I");
	ss[31].setArtistName("G-Eazy");
	ss[31].setGenre("Pop");
	ss[31].setReleaseDate("14/10/2015");
	ss[31].setLyrics("Ooh, it's just me, myself and I Solo ride until I die 'Cause I got me for life (yeah) Ooh, I don't need a hand to hold Even when the night is cold I got that fire in my soul (ah) And as far as I can see, I just need privacy Plus a whole lot of tree, fuck all this modesty I just need space to do me Give the world what they're tryna see A Stella Maxwell right beside of me A Ferrari, I'm buyin' three A closet of Saint Laurent, get what I want when I want 'Cause this hunger is drivin' me, yeah I just need to be alone, I just need to be at home Understand what I'm speakin' on If time is money I need a loan But regardless I'll always keep keepin' on Fuck fake friends We don't take L's, we just make M's While y'all follow, we just make trends I'm right back to work when that break ends Ooh (yeah), it's just me, myself and I Solo ride until I die 'Cause I got me for life (got me for life, yeah) Ooh, I don't need a hand to hold Even when the night is cold I got that fire in my soul I don't need anything (yeah) to get me through the night Except the beat that's in my heart Yeah, it's keepin' me alive (keeps me alive) I don't need anything to make me satisfied (you know) 'Cause the music does me good And it gets me every time (yeah) And I don't like talkin' to strangers So get the fuck off me, I'm anxious I'm tryna be cool, but I may just go apeshit Say, Fuck y'all to all of y'all faces It changes though now that I'm famous Everyone knows how this lifestyle is dangerous But I love it, the rush is amazin' Celebrate nightly and everyone rages I found how to cope with my angers, I'm swimmin' in money Swimmin' in liquor, my liver is muddy But it's all good, I'm still sippin' this bubbly, this shit is lovely This shit ain't random, I didn't get lucky Made it right here 'cause I'm sick with it, cuddy They all take the money for granted But don't want to work for it, tell me now, isn't it funny? Ooh (nah), it's just me, myself and I Solo ride until I die 'Cause I got me for life (got me for life, yeah) Ooh, I don't need a hand to hold Even when the night is cold I got that fire in my soul I don't need anything (yeah) to get me through the night Except the beat that's in my heart Yeah, it's keepin' me alive (keeps me alive) I don't need anything to make me satisfied (you know) 'Cause the music does me good And it gets me every time like, ba-ba-ba-ba-da-ba Ba-ba-ba-da-ba (yeah) Ba-ba-ba-ba-da-ba Ba-ba-ba-da-ba Ba-ba-ba-ba-da-ba Ba-ba-ba-da-ba 'Cause the music does me good And it gets me every time Yeah, lonely nights I laid awake Pray to Lord my soul to take My heart's become too cold to break Know I'm great, but I'm broke as hell Havin' dreams that I'm foldin' cake All my life I've been told to wait But I'ma get it now, yeah, it's no debate Ooh (yeah), it's just me, myself and I Solo ride until I die 'Cause I got me for life (got me for life, yeah) Ooh, I don't need a hand to hold Even when the night is cold I got that fire in my soul I don't need anything (yeah) to get me through the night Except the beat that's in my heart Yeah, it's keepin' me alive (keeps me alive) I don't need anything to make me satisfied (you know) 'Cause the music does me good And it gets me every time");
	
	ss[32].setSongName("Him-&-I");
	ss[32].setArtistName("G-Eazy");
	ss[32].setGenre("Electronic");
	ss[32].setReleaseDate("30/11/2017");
	ss[32].setLyrics("Cross my heart, hope to die To my lover, I'd never lie He said be true,  I swear I'll try In the end, it's him and I He's out his head, I'm out my mind We got that love, the crazy kind I am his, and he is mine In the end, it's him and I, him and I My '65 speeding up the PCH, a hell of a ride They don't wanna see us make it, they just wanna divide 2017 Bonnie and Clyde Wouldn't see the point of living on if one of us died, yeah Got that kind of style everybody try to rip off YSL dress under when she takes the mink off Silk on her body, pull it down and watch it slip off Ever catch me cheating, she would try to cut my (ha-ha-ha) Crazy, but I love her, I could never run from her Hit it, no rubber never would let no one touch her Swear we drive each other, mad, she be so stubborn But, what the fuck is love with no pain, no suffer Intense, this shit, it gets dense She knows when I'm out of it like she could just sense If I had a million dollars or was down to ten cents She'd be down for whatever, never gotta convince (you know?) Cross my heart, hope to die To my lover, I'd never lie (I love you baby) He said be true, I swear I'll try In the end, it's him and I He's out his head, I'm out my mind We got that love; the crazy kind I am his, and he is mine In the end, it's him and I Him and I Woah-oh-oh-oh-oh Woah-oh-oh-oh-oh In the end, it's him and I Him and I Woah-oh-oh-oh-oh Woah-oh-oh-oh-oh In the end, it's him and I It's her and I, mobbin' 'til the end of time Only one who gets me, I'm a crazy fuckin' Gemini Remember this for when I die Everybody dressed in all black, suits and a tie My funeral will be lit if I- Ever go down or get caught, or they identify My bitch was the most solid, nothing to solidify She would never cheat, you'd never see her with a different guy Ever tell you different, then it's a lie See, that's my down bitch, see that's my soldier She keeps that thang-thang if anyone goes there Calm and collected, she keeps her composure And she gon' ride for me until this thing over We do drugs together (together), fuck up clubs together (together) And we'd both go crazy (crazy) if we was to sever You know? We keep mobbin', it's just me and my bitch Fuck the world, we just gon' keep getting rich, you know? Cross my heart, hope to die To my lover, I'd never lie He said be true,  I swear I'll try In the end, it's him and I He's out his head, I'm out my mind We got that love; the crazy kind I am his, and he is mine In the end, it's him and I Him and I Woah-oh-oh-oh-oh Woah-oh-oh-oh-oh In the end, it's him and I Him and I Woah-oh-oh-oh-oh Woah-oh-oh-oh-oh In the end, it's him and I Cross my heart, hope to die To you, I've never lied For you, I'd take a life It's him and I, and I swear (ayy) 'Til the end I'ma ride wit' you Mob and get money, get high wit' you, yeah (ayy) Cross my heart, hope to die This is our ride or die You can confide in me There is no hiding, I swear Stay solid, never lie to you Swear, most likely I'ma die wit' you, yeah Cross my heart, hope to die To my lover, I'd never lie He said be true,  I swear I'll try In the end, it's him and I He's out his head, I'm out my mind We got that love, the crazy kind I am his, and he is mine In the end, it's him and I Him and I Woah-oh-oh-oh-oh Woah-oh-oh-oh-oh In the end, it's him and I");
	
	ss[33].setSongName("CHAL");
	ss[33].setArtistName("Shamoon Ismail");
	ss[33].setGenre("Hip hop");
	ss[33].setReleaseDate("30/08/2019");
	ss[33].setLyrics("Do it my way Banaai kallay mein sarak Agg naal, kadi baraf Pio davay mein jharak Akhay apne aap nu parak Cause no money in purse Naal fly honies, no tharak Veere asaan dovaan ich farak Tusi act hard aiween garaj Tusi act hard kadi baras You act hard par toon naram Jidoon samne jaande laraz Hun message loki meinu keran Hun sunan ganay meray cousin Hun challay naal poori nasal Inhaan dasnaan mera faraz Veere leya nae kadi karaz Kadi mangi nae assi madad Veere rab da ey bara karam Munda shine keray jivain farash Munda rhyme keray pi ke charas Tuaday khokhlay saray bharam Meinu rok le mera maraz Pichay bolde tusi shut up Sun Big bass, champagne, thick haze Underground nae o disde Aiween te nae veere likhde Aiween kadi nae o vikde Aiween te nae kharay tikk ke Locked in, 6th day Taanvi run up quick tez Chal Big bass, champagne, thick haze Underground nae o disde Aiween te nae veere likhde Aiween kadi nae o vikde Aiween te nae kharay tikk ke Locked in, 6th day Pull up on you quick tezz Chal, Chal, yeah, Chal");
	
	ss[34].setSongName("Faasla");
	ss[34].setArtistName("Shamoon Ismail");
	ss[34].setGenre("Hip hop");
	ss[34].setReleaseDate("13/09/2021");
	ss[34].setLyrics("Jithay munda javey make it hot jivain garmi ich agra Slide kara treats for the party gaddi kaali haigi drop top Jithay jaake labna e labna ne tenu sadday naal da Ae munde kaanu kar dene flex kaanu kar de muqabla? Ik baad ik lawein agge kuri style tera top da Kadd lawein dil mundeyan de soni kardi ne aasra Dasde ne yaar tere saanu tera saryaan naal rabta Khedna ae khed naal saddey thora chhad ke ni faasla Ik baad ik lawein agge kuri style tera top da Kadd lawein dil mundeyan de soni kardi ne aasra Dasde ne yaar tere saanu tera saryaan naal rabta Khedna ae khed naal saddey thora chhad ke ni faasla Yaar tere akheya si menu hega ne ae mera raasta Yaar mere puchde sawaal naal piece laa ke glock da Maan geya teriya'n adava'n sohni dil saada soft aa Maan geya nazra'n nu teri munda kar ditta lock up Labna koi hor nai Dil mera addi koi zor nai Bad girl kare shor sahi Meethi baatein kam, woh chahti poora tor bhai I dont wanna say much if you don't got anytime Seen a lotta like you cross my line Itna sochu nahi just make your mind up Ek aur din lele girl i might change my mind Pen down gaane likhay tere vaastey Baatein yaad nai uss raat hum jahaaz thay Meri peeth peeche baato'n ka jawab de Sab launde mere issi baat pe naraaz thay Woh bole you gotta look out for yourself now Ye laanjhe theek nahi khud mein ab ye samjhau'n Par dil phenk mein jab bhi tuu aaye saamne Just roll some mo baby jitna marzi kaam le Ik baad ik lawein agge kuri style tera top da Kadd lawein dil mundeyan de soni kardi ne aasra Dasde ne yaar tere saanu tera saryaan naal rabta Khedna ae khed naal saddey thora chhad ke ni faasla Faasla Thora sa toh laaj rakh, rakh thora faasla No. tera paas tha, Thora sa toh laaj rakh, rakh thora faasla");
	
	ss[35].setSongName("Promises");
	ss[35].setArtistName("Shamoon Ismail");
	ss[35].setGenre("Pop");
	ss[35].setReleaseDate("24/09/2021");
	ss[35].setLyrics("Assi girday han uthtay han, tur day han rukday na Tere khyal mukday na, tu bass meri dost Thora nera ban ja tu light, mai asal karan recognize Teri khamiyan mai keeti side tay, can you do the same though? Mai jarnda thora kam honr aala Dus How to be, a better man, and I'll follow it Mai jarnda thora kam honr aala Teach me How to be, a better man, and I'll follow it Dil teri raah puchda hai, chalda tere naal rukda hai Tera khyal rawain kol tu Dil teri raah puchda hai Rehnda paas kadi duur dil sada majboor, sun le meri kadi tu Chaaya hai tera fitoor Saddiyan da waada tere da irada mennu Das dei tu keri galli murna ae chaunda Logan nun mai ki dassan, piyar tu nayi nibhanra Rab tunn mai manga duawaan maahi tu na jaa Dil teri raah puchda ey Chalda, tere naal rukda ey Tera khyal rawain kol tu Dil teri raah puchda hai I put my heart on the line too Lagay mennu mere liye bass tu kho gaye si assi kisi paar I see you now, tu hi mera piyar Tu hi meri guiding light, mai han tera ride or die Chayi da ki dass I will plan for you I'll be the man for you Dil teri raah puchda ey Chalda, tere naal rukda ey Tera khyal rawain kol tu Dil teri raah puchda hai");
	
	ss[36].setSongName("Magic");
	ss[36].setArtistName("Shamoon Ismail");
	ss[36].setGenre("Pop");
	ss[36].setReleaseDate("11/04/2019");
	ss[36].setLyrics("I see you dancing Lagdi ey kurri tu fancy Ey saare munday vi flexing Lagda je apna te chance nae tanvi I make them go Just how I roll Ey bolan o Tu jivian gold Yeah Kalli khaloti ey samne meri Sunna wan gallan bitha ke mein teri Toon gallan sab chor na ve Aa ja mairay kol na ve Mein dil tere naal la ke Toon dil maira tor na je Toon gallan sab chor na ve Aa ja mairay kol na ve Mein dil tere naal la ke Toon dil maira tor na je Toon gallan sab chor na ve Toon dil maira tor na je Toon gallan sab chor na Toon gallan sab chor na I make them go Just how I roll Ey bolan o Tu jivian gold Kalli khaloti ey samne meri Sunna wan gallan bitha ke mein teri Toon gallan sab chor na ve Aa ja mairay kol na ve Mein dil tere naal la ke Toon dil maira tor na je Toon gallan sab chor na ve Aa ja mairay kol na ve Mein dil tere naal la ke Toon dil maira tor na je");
	
	ss[37].setSongName("Rung");
	ss[37].setArtistName("Shamoon Ismail");
	ss[37].setGenre("Indie");
	ss[37].setReleaseDate("30/01/2020");
	ss[37].setLyrics("Rakhde nae gallan dil ich Sunne nae aya gillay Das denda para jidoon hillay Dus na dobara saanu milay Step in the room jivain villain I see you move, see you kill it Toon kita naira aithay dinnay You know you got me in my feelings Laggi je agg loki jam-packed Vakh meri vibe but she catch that Vekhaan mein lights aanday flashback Look in my eyes, in my eyes, dus Dus ki samajhdi ain toon Dus ki samajhdi ain toon Vekhdi ain rung like I do? Like I do No you dont stop Toon hillain jivain rockstars Akhaan choon boldi ain tere Akhain toon hold me nairay Hold me nairay Laggi je agg loki jam packed Vakh meri vibe but she catch that Vekhaan mein lights aanday flashback Look in my eyes, in my eyes, dus Dus ki samajhdi ain toon Dus ki samajhdi ain toon Dus ki samajhdi ain toon Vekhdi ain rung like I do? Like I do");

	//Creating linked lists (albums)
	linkedList l1;
	linkedList l2;
	linkedList AlanWalker;
	linkedList Eminem;
	linkedList Prznt;
	linkedList LanaDelRey;
	linkedList Weeknd;
	linkedList Geazy;
	linkedList ShamoonIsmail;

	//Inserting the songs in the respective linked lists (albums)
	for(int i = 0; i < 2; i++) {
		l1.insertNode(&ss[i]);
	}
	
	l2.insertNode(&ss[2]);
	
	for(int i = 3; i < 8; i++) {
		AlanWalker.insertNode(&ss[i]);
	}
	
	for(int i = 8; i < 13; i++) {
		Eminem.insertNode(&ss[i]);
	}
	
	for(int i = 13; i < 18; i++) {
		Prznt.insertNode(&ss[i]);
	}
	
	for(int i = 18; i < 23; i++) {
		LanaDelRey.insertNode(&ss[i]);
	}
	
	for(int i = 23; i < 28; i++) {
		Weeknd.insertNode(&ss[i]);
	}
	
	for(int i = 28; i < 33; i++) {
		Geazy.insertNode(&ss[i]);
	}
	
	for(int i = 33; i < 38; i++) {
		ShamoonIsmail.insertNode(&ss[i]);
	}
	
	//Creating the binary tree
	binaryTree bb;
	
	//Inserting the albums in the binary tree
	bb.insertNode(&l1);
	bb.insertNode(&l2);
	bb.insertNode(&AlanWalker);
	bb.insertNode(&Eminem);
	bb.insertNode(&Prznt);
	bb.insertNode(&LanaDelRey);
	bb.insertNode(&Weeknd);
	bb.insertNode(&Geazy);
	bb.insertNode(&ShamoonIsmail);
	
	bb.user();
}
