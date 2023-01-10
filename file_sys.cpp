/** 
 * This file contains the file system functions that you need to implement.
 * You can define helper functions in this file.
 * 
 * Remember to remove the initial statements in the functions.
 * They are only used so that your semi-finished codes can compile.
*/

//started 5:18pm 30/April
#include <iostream>
#include "file_sys.h"
#include "utils.h"
using namespace std;

int createFile(Dir *dir, const char *name, unsigned int size, Tag tag)
{
    // make file psudocode

    // validate name meets requirements DONE

    //check if dir or name is null;
    if (dir == nullptr || name == nullptr) {
        //debugging
        //cout << "Either Dir or Name is NULL" << endl;
        return 1;
    }

    //check is name is valid
    string str_name = name;
    int found = str_name.find_first_not_of("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm01234567890.-_");
    if (found != string::npos)
    {
        //debugging purpose
        //cout << "Found an invalid char: " << str_name[found] << endl;
        return 2; 

    } else if (str_name[0] == '\0' || str_name[0] == '.' && str_name[1] == '\0' 
            || str_name[0] == '.' && str_name[1] == '.' && str_name[2] == '\0' || str_name[0] == '-') 
    {
        //more debugging
        //cout << "The name either was . or .. or empty" << endl;
        return 2;
    } 

    //check if name matches with ANY other directory
    //if there are folders to check the name
    for (Dir* p = dir->subdir; p != nullptr; p=p->next) {
        if (strcmp(name, p->name) == 0) {
            //debugging
            //cout << "the name is the same as a directory" << endl;
            return 3;
        }
    }

    //check if the name matches with any other file
    // if there are files to check
    for (File* p = dir->subfile; p != nullptr; p=p->next) {
        if (strcmp(name, p->name) == 0) {
            //debugging
            //cout << "the name is the same as a file" << endl;
            return 3;
        }        
    }
    //check if the current direction has a file already
    // if not, 
        //create a new file object, 
        // with name of name, tag of tag, size of size, parent of dir, and next of nullpointer
        // set dir subfile to point to the new created file object.
    // otherwise
        // create a new file object, 
        // with name of name, tag of tag, size of size, parent of dir, and next of nullpointer
        // start at dir->subfile, then keep checking dir->subfile->next until == nullpointer, set this found instance to the created new file object.
    if (dir->subfile == nullptr) {
        File *p_file = new File;
        strcpy(p_file->name, name);
        p_file->size = size;
        p_file->tag  = tag;
        p_file->parent = dir;
        p_file->next = nullptr;
        dir->subfile = p_file;
    } else {
        File *p_file = new File;
        strcpy(p_file->name, name);
        p_file->size = size;
        p_file->tag  = tag;
        p_file->parent = dir;
        p_file->next = dir->subfile;
        dir->subfile = p_file;
    }

    return 0;  // Remove this line after you finish.
}

int createDir(Dir *dir, const char *name)
{
    //check if dir or name is null;
    if (dir == nullptr || name == nullptr) {
        //debugging
        //cout << "Either Dir or Name is NULL" << endl;
        return 1;
    }
    //check is name is valid
    string str_name = name;
    int found = str_name.find_first_not_of("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm01234567890.-_");
    if (found != string::npos)
    {
        //debugging purpose
        //cout << "Invalid char: " << str_name[found] << endl;
        return 2; 

    } else if (str_name[0] == '\0' || str_name[0] == '.' && str_name[1] == '\0' 
            || str_name[0] == '.' && str_name[1] == '.' && str_name[2] == '\0' || str_name[0] == '-') 
    {
        //more debugging
        //cout << "The name either was . or .. or empty" << endl;
        return 2;
    } 

    //check if name m atches with ANY other directory
    //if there are folders to check the name
    for (Dir* p = dir->subdir; p != nullptr; p=p->next) {
        if (strcmp(name, p->name) == 0) {
            //debugging
            //cout << "the name is the same as a directory" << endl;
            return 3;
        }
    }

    //check if the name matches with any other file
    // if there are files to check
    for (File* p = dir->subfile; p != nullptr; p=p->next) {
        if (strcmp(name, p->name) == 0) {
            //debugging
            //cout << "the name is the same as a file" << endl;
            return 3;
        }        
    }


 //check if the current direction has a directory already
    // if not, 
        //create a new directory object, 
        //with name of name, parent of dir, subdir of nullptr, subfile of nullptr, next of nullptr;
        //set dir subdir to point to the new created directory object.
    // otherwise
        // create a new file object, 
        // with name of name, parent of dir, subdir of nullptr, subfile of nullptr, next of nullptr;
        // start at dir->subdir, then keep checking dir->subfile->next until == nullpointer,
        // set this found instance to the created new file object.

    if (dir->subdir == nullptr) {
        Dir *p_dir = new Dir;
        strcpy(p_dir->name, name);
        p_dir->subdir = nullptr;
        p_dir->subfile= nullptr;
        p_dir->parent = dir;
        p_dir->next = nullptr;
        dir->subdir = p_dir;
        //cout << "Bet!" << dir->subdir << endl;
    } else {
        Dir *p_dir = new Dir;
        strcpy(p_dir->name, name);
        p_dir->subdir = nullptr;
        p_dir->subfile= nullptr;
        p_dir->parent = dir;
        p_dir->next = dir->subdir;
        dir->subdir = p_dir;
    }


    return 0;  // Remove this line after you finish.
}

int deleteFile(Dir *dir, const char *name)
{
    //check if dir or name is null;
    if (dir == nullptr || name == nullptr) {
        //debugging
        //cout << "Either Dir or Name is NULL" << endl;
        return 1;
    }

    bool found = false;
    //check if the name matches with with name called, meaning it can be deleted.
    if (dir->subfile != nullptr) {
        for (File* p = dir->subfile; p != nullptr; p=p->next) {
            if (strcmp(name, p->name) == 0) {
                found = true;
            }        
        }
    }

    if (found != true) {
        return 2;
    }


    File* p_previous_file = nullptr;
    File* p_current_file = dir->subfile;

    while (p_current_file!= nullptr && strcmp(p_current_file->name, name) != 0) {
        p_previous_file = p_current_file;
        p_current_file = p_current_file->next;
        if (p_current_file == nullptr) {
            return 2;
        }
    }
    if (p_current_file != nullptr) {
        // if head;
        if (p_current_file == dir->subfile) {
            dir->subfile = p_current_file->next;
        }
        else {
            p_previous_file->next = p_current_file->next;
        }
        delete p_current_file;
        p_current_file = nullptr;
    }
    

    return 0;  // Remove this line after you finish.
}

void delete_all_files (File* head) 
{
    if (head == nullptr) 
        return;

    if (head->next != nullptr) {
        delete_all_files(head->next);
    }

    //cout << "deleted: " << head->name << endl;
    delete head; 
    head = nullptr;
}



int deleteDir(Dir *dir, const char *name, bool recursive, int recursive_count)
{
    //check if dir or name is null;
    if (dir == nullptr || name == nullptr) {
        //debugging
        //cout << "Either Dir or Name is NULL" << endl;
        return 1;
    }

    bool found = false;
    // if no directories exist in dir.
    //check if the name matches with with name called, meaning it can be deleted.
    if (dir->subdir != nullptr) {
        for (Dir* p = dir->subdir; p != nullptr; p=p->next) {
            if (strcmp(name, p->name) == 0) {
                found = true;
            }        
        }
    } 
    if (found != true) {
        return 2;
    }


    Dir* p_previous_dir = nullptr;
    Dir* p_current_dir = dir->subdir;

    while (p_current_dir!= nullptr && strcmp(p_current_dir->name, name) != 0) {
        p_previous_dir = p_current_dir;
        p_current_dir = p_current_dir->next;
        // if can get to end of directory linked list without findint one that matches name
        if (p_current_dir == nullptr) {
            return 2;
        }
    }
    // otherwise
    // if the found folder is empty delete it.
    if (p_current_dir->subdir == nullptr && p_current_dir->subfile == nullptr && recursive_count == 0) {
        // if head;
        if (p_current_dir == dir->subdir) {
            dir->subdir = p_current_dir->next;
        }
        else {
            p_previous_dir->next = p_current_dir->next;
        }
        //cout << "deleted here!: " << p_current_dir->name << " recursive_count: " << recursive_count << endl;
        delete p_current_dir;
        p_current_dir = nullptr;

    } else if (recursive == false) {
        return 3;

    } else if (recursive == true) {

        //check if there are files in the directory to be deleted.
        //delete all files.
        if (p_current_dir->subfile != nullptr) {
            delete_all_files(p_current_dir->subfile);
            p_current_dir->subfile = nullptr;
        }

        //check if there are sub directories in the directory to be deleted.
        if (p_current_dir->subdir != nullptr) {
        // vertical deletion
            //cout << "entered recursion vertical deletion: " << recursive_count << endl;
            deleteDir(p_current_dir, p_current_dir->subdir->name, true, recursive_count+1);
        }

        // horizontal deletion
        if (p_current_dir->next != nullptr && recursive_count != 0) {
            //cout << "p_current is: " << p_current_dir->name << " next is: " << p_current_dir->next->name << endl;
            //cout << "entered recursion horizontal deletion: " << recursive_count << endl;
            deleteDir(p_current_dir->parent, p_current_dir->next->name, true, recursive_count+1);
        }


        //lastly, after all sub folder and sub files have been deleted.
        if (p_current_dir == dir->subdir) {
            dir->subdir = p_current_dir->next;
        }
        else {
            p_previous_dir->next = p_current_dir->next;
        }
        //cout << "deleted: " << p_current_dir->name << endl;
        delete p_current_dir;
        p_current_dir = nullptr;
    }


    return 0;  // Remove this line after you finish.
}

int deleteDir(Dir *dir, const char *name, bool recursive) {
    return deleteDir(dir, name, recursive, 0);
}

//TODO: testcase 69 broken.

unsigned int get_all_files_size (File* head) 
{
    if (head == nullptr) 
        return 0;

    if (head->next != nullptr) {
        return head->size + get_all_files_size(head->next);
    }
    else {
        return head->size;
    }

}

unsigned int getSize(const Dir *dir, int recursive_count)
{
    // If the directory is empty, return 0.
    if (dir->subdir == nullptr && dir->subfile == nullptr) {
        return 0;
    }
    
    int size_dir = 0;

    //if there are subfiles
    if (dir->subfile != nullptr) {
        size_dir += get_all_files_size(dir->subfile);
    }

    // if there are sub-directories
    if (dir->subdir != nullptr) {
        size_dir += getSize(dir->subdir, recursive_count+1);
    }

    if (dir->next != nullptr && recursive_count != 0) {
        size_dir += getSize(dir->next, recursive_count+1);
    }

    return size_dir;   // Remove this line after you finish.
}

unsigned int getSize(const Dir *dir) {
    return getSize(dir, 0);
}

void countTags (const Dir* dir, Tag tag, unsigned int &length, int recursive_count) {

    // check FILES

    if (dir->subfile != nullptr) {
        for (File *p = dir->subfile; p!= nullptr; p=p->next) {
            //cout << "checking: " << p->name <<endl;
            if (p->tag == tag) {
                //cout << "found one! p->tag is: " << p->tag << endl;
                length++;
            }
        }
    }

    // check other DIRECTORIES
    if (dir->next != nullptr && recursive_count != 0) {
        countTags(dir->next, tag, length, recursive_count+1);
    }

    if (dir->subdir != nullptr) {
        countTags(dir->subdir, tag, length, recursive_count+1);
    }

}

File* pointerAtLength (const Dir* dir, Tag tag, unsigned int &length, int recursive_count, int &found_tags) {
    // check FILES
    //cout << "recrusive count is:" << recursive_count << endl;
    if (dir->subfile != nullptr) {
        for (File *p = dir->subfile; p!= nullptr; p=p->next) {
            if (p->tag == tag) {
                //cout << "found a tag: " << p->name << endl;
                //cout << "               found_tags is: " << found_tags << " length is: " <<length << endl;
                if (found_tags == length) {
                    length++;   
                    return p;
                }
                found_tags++;
                //cout << "found_tags is INCREASED TO : " << found_tags << " length is: " <<length << endl;
                //cout << endl;
            }
        }
    }

    // check other DIRECTORIES
    if (dir->next != nullptr && recursive_count != 0) {
        return pointerAtLength(dir->next, tag, length, recursive_count+1, found_tags);
    }

    if (dir->subdir != nullptr) {
        return pointerAtLength(dir->subdir, tag, length, recursive_count+1,found_tags);
    }
    return nullptr;   
}



// This function looks for all the files of a certain tag and returns them in a dynamic array.
// const Dir* dir: will search recursively under this directory.
// Tag tag: the target tag.
// unsigned int& length: an unsigned integer passed by reference. 
// Its value should be the size of the returned dynamic array (number of elements) after this function returns.
// This function returns a dynamic array of pointers. Each pointer here points to a file of the specified tag. 
// Also remember to set length to the correct value. 
// If dir is null or you cannot find any files of that tag, length should be set to 0 and the function should return null. 
// Don't create a dynamic array with size 0. The order of the pointers doesn't matter, we will sort your array while grading.

const File **filesOfTag(const Dir *dir, Tag tag, unsigned int &length)
{   
    if (dir == NULL) {
        length = 0;
        return nullptr;
    }

    // incase passed length is garbage?...
    length = 0;

    // will update length to the number of found files with tag; tag.
    countTags(dir, tag, length, 0);
    //cout << "length is: " << length << endl;
    
    if (length != 0) {
        const File **arr = new const File*[length];
        int max_length = length;
        int found_tags = 0;
        int k = 0;
        length = 0;
        while (k < max_length) {
            found_tags = 0;
            //cout << "setting arr[k] where k is: " << k  << endl;;
            arr[k] = pointerAtLength(dir, tag, length, 0, found_tags);
            //cout << "arr[" << k << "] set to: " << arr[k]->name << endl;
            k++;
            //cout << "k: " << k << endl;

        }
        return arr;
    } else {
        //cout << "hi: returning nullptr" << endl;
        length = 0;
        return NULL;
    }

    

}



// This function moves files. It returns an integer status code.
// File* tgt: the target file to be moved.
// Dir* dest: the destination directory.
// The target file will be removed from the old linked list and added to the head of the new linked list. 
// This function will return:
// -1: when the function is not yet implemented. The skeleton codes always return -1, remove that line after you finished this function.
// 1: when parameter tgt or dest is null.
// 2: when dest is the parent of tgt, then the moving operation is meaningless, the file should stay at its original position in the linked list.
// 3: when there is a name conflict (the name of tgt is already taken by something under dest).
// 0: when nothing above happens and the file is successfully moved.
// Again, return the smallest one if there are multiple errors.
int moveFile(File *tgt, Dir *dest)
{
    if (tgt == NULL || dest == NULL) {
        return 1;
    }

    if (tgt->parent == dest) {
        return 2;
    }

    for (File* p = dest->subfile; p != nullptr; p=p->next) {
        if (strcmp(tgt->name, p->name) == 0) {
            //debugging
            //cout << "the name is the same as a file" << endl;
            return 3;
        }        
    }

    //check if name matches with ANY other directory
    //if there are folders to check the name
    for (Dir* p = dest->subdir; p != nullptr; p=p->next) {
        if (strcmp(tgt->name, p->name) == 0) {
            //debugging
            //cout << "the name is the same as a directory" << endl;
            return 3;
        }
    }


    // remove from old directory
    // if tgt is the head file of the old directory (parent)
    File* p_previous_file = nullptr;
    File* p_current_file = tgt->parent->subfile;

    while (p_current_file!= nullptr && p_current_file != tgt) {
        p_previous_file = p_current_file;
        p_current_file = p_current_file->next;
    }
    if (p_current_file != nullptr) {
        // if head;
        if (p_current_file == tgt->parent->subfile) {
            tgt->parent->subfile = p_current_file->next;
        }
        else {
            p_previous_file->next = p_current_file->next;
        }
    }

    // move file to new directory
    // if new directory has no subfiles
    if (dest->subfile == nullptr) {
        dest->subfile = tgt;
        tgt->next = nullptr;
        tgt->parent = dest;
    } else {
        tgt->next = dest->subfile;
        dest->subfile = tgt;
        tgt->parent = dest;
    }

    
    return 0;     // Remove this line after you finish. 
}


// returns true if destination (dest) is a descendent of target (tgt)
bool checkDescendents (Dir* tgt, Dir* dest, int recursive_count) {
    
    if (tgt == dest) {
        return true;
    }

    if (tgt->next != nullptr && recursive_count != 0) {
        return checkDescendents(tgt->next, dest, recursive_count+1);
    }

    if (tgt->subdir != nullptr) {
        return checkDescendents(tgt->subdir, dest, recursive_count+1);
    }

    return false;
}


// This function moves directories. It returns an integer status code.
// Dir* tgt: the target directory to be moved.
// Dir* dest: the destination directory.
// Note that a directory cannot be moved to any of its descendants (a descendant is a sub-directory or a sub-sub-directory or sub-sub-sub ...). 
// This is because the descendants will also be moved together with the target, so they cannot be the destination. 
// The target directory will be added to the head of the new linked list. This function will return:
// -1: when the function is not yet implemented. The skeleton codes always return -1, remove that line after you finished this function.
// 1: when parameter tgt or dest is null.
// 2: when dest is the parent of tgt, then the moving operation is meaningless, the directory should stay at its original position in the linked list.
// 3: when there is a name conflict (the name of tgt is already taken by something under dest).
// 4: when dest is a descendant of tgt.
// 0: when nothing above happens and the directory is successfully moved.
// Again, return the smallest one if there are multiple errors.

int moveDir(Dir *tgt, Dir *dest)
{
    if (tgt == NULL || dest == NULL) {
        return 1;
    }

    if (dest == tgt->parent) {
        return 2;
    }

    for (File* p = dest->subfile; p != nullptr; p=p->next) {
        if (strcmp(tgt->name, p->name) == 0) {
            //debugging
            //cout << "the name is the same as a file" << endl;
            return 3;
        }        
    }

    //check if name matches with ANY other directory in parent
    for (Dir* p = dest->subdir; p != nullptr; p=p->next) {
        if (strcmp(tgt->name, p->name) == 0) {
            //debugging
            //cout << "the name is the same as a directory" << endl;
            return 3;
        }
    }


    if ( checkDescendents(tgt, dest, 0) == true) {
        return 4;
    } 

    // remove from old directory
    // if tgt is the head DIR of the old directory (parent)
    Dir* p_previous_dir = nullptr;
    Dir* p_current_dir = tgt->parent->subdir;

    while (p_current_dir!= nullptr && p_current_dir != tgt) {
        p_previous_dir = p_current_dir;
        p_current_dir = p_current_dir->next;
    }
    if (p_current_dir != nullptr) {
        // if head;
        if (p_current_dir == tgt->parent->subdir) {
            tgt->parent->subdir = p_current_dir->next;
        }
        else {
            p_previous_dir->next = p_current_dir->next;
        }
    }

    // move dir to new directory
    // if new directory has no subfiles
    if (dest->subdir == nullptr) {
        dest->subdir = tgt;
        tgt->next = nullptr;
        tgt->parent = dest;
    } else {
        tgt->next = dest->subdir;
        dest->subdir = tgt;
        tgt->parent = dest;
    }


    return 0;    
}
