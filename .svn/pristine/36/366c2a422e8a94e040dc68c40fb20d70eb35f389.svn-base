#ifndef dbrow
#define dbrow() auto lmrow = stmt.row(); auto *lengths = stmt.lengths();
#endif

#ifndef streq
#define streq(X,Y) std::string X; X.append(lmrow[Y],lengths[Y]); output.append(string_serialize(X)); 
#endif

#ifndef discern
#define discern(X) std::string X = non_safe_string_deserialize(b);
#endif
struct ModelServerNetmodule : public net_module {
    void initialize() {
        mPlayer->netbind(mPlayer,&inet_player::getModelList, OLC, GetModelList);
//        mPlayer->netbind(mPlayer,&inet_player::ModifyModel, OLC, ModifyModel);
	mPlayer->netbind(mPlayer,&inet_player::uploadModel, OLC, AddModel);
	mPlayer->netbind(mPlayer,&inet_player::getModelTimestamp, OLC, ModelTimestamp);
//        mPlayer->netbind(mPlayer,&inet_player::deleteModel, OLC, DeleteModel);
        mPlayer->netbind(mPlayer,&inet_player::getModel, OLC, GetModelDetails);
    }
};
ModelServerNetmodule frankenstein_is_a_work_of_literature;

void inet_player::getModelList(std::vector<std::string>&in) {
	/// Get a list of models and id's, return them to client as string name string id
	if(!admin) {
		std::cout << "Non admin requesting model list\n";
	}
	std::string qry = "select id, originalFilename from FileStorage";
	MySQL_Helper::Query stmt(database_connection); 
	stmt.prepare(qry);
	stmt.run();
	std::string output;
	output+= (to_value(OLC));
	output+= (to_value(GetModelList));
	for(int x = 0; x < stmt.numrows; ++x) {
		dbrow()
		streq(id, 0)
		streq(originalFilename,1)
	}
	send_text(output, socket);
}

void inet_player::getModelTimestamp(std::vector<std::string>&in) {
	MySQL_Helper::Query stmt(database_connection);
	std::string query = "select timestamp from FileStorage where id='?'";
	std::string &b = in[0];
	discern(str_id);
	stmt.prepare(query, str_id);
	stmt.run();
	std::string output;
	output += to_value(OLC);
	output += to_value(ModelTimestamp);
	output.append(string_serialize(str_id));
	if(stmt.numrows == 0) {
		std::string zero = to_string((unsigned int)0);
		output.append(string_serialize(zero));
	} else {
		dbrow()
		streq(timestamp, 0)
	}
	send_text(output, socket);
}
void inet_player::getModel(std::vector<std::string>&in) {
	MySQL_Helper::Query stmt(database_connection);
	std::string query = "select file, type, originalFilename, timestamp from FileStorage where id='?'";
	std::string b = in[0];
	discern(str_id);
	discern(cl_timestamp);
	stmt.prepare(query,str_id);
	std::string output;
	output += to_value(OLC);
	output += to_value(GetModelDetails);
	if(stmt.numrows == 0) { 
		std::cout << "Model data requested but none found!\n";
		output.append(to_string((unsigned int)0));
	} else {
		dbrow()
		output.append(string_serialize(str_id));
		streq(file,0)
		streq(type,1)
		streq(originalFilename, 3)
		streq(timestamp, 4)
	}
	send_text(output, socket);
}
struct ulmodel {
	std::string filename;
	std::string filecontents;
	ulmodel(): filename(""), filecontents(""){}
	ulmodel(const std::string &_filename, const std::string &_filecontents) :
	filename(_filename),filecontents(_filecontents){}
};
void insert_ulmodels_into_db(std::vector<ulmodel> &inc) {
	MySQL_Helper::Query stmt(database_connection);
	std::string query;
	for(auto i=inc.begin(), e = inc.end(); i!=e; ++i) {
		size_t pi = (*i).filename.find_first_of(".");
		if(pi==std::string::npos || pi==(*i).filename.size()-1 ) {
		    std::cout << "(Skipping upload)Invalid filename: " << (*i).filename<<std::endl;
		    continue;
		}
		pi+=1;
		std::string ext = (*i).filename.substr(pi,(*i).filename.size()-pi);
		// find out if ext is valid.
		query = "select type from FileExtensions where ext='?'";
		stmt.prepare(query,ext);
		stmt.run();
		if(stmt.numrows ==0) {
		    std::cout << "(Skipping upload)Invalid file extension" << (*i).filename<<std::endl;
		    continue;
		}
		MYSQL_ROW& lmrow = stmt.row();
		unsigned long *lengths = mysql_fetch_lengths(stmt.result()); // Need to try to delete[] this..     
		std::string typeidstr; typeidstr.append(lmrow[0],lengths[0]);
		unsigned int tid = fromstring<unsigned int>(typeidstr);
		query = "insert into FileStorage(file, type, originalFilename, FileSize) values ('?','?','?','?')";
		stmt.prepare(query, (*i).filecontents, tid, (*i).filename, (*i).filecontents.size());
		stmt.run();
	}
}
void inet_player::uploadModel(std::vector<std::string>&in) {
/*
 *  This function is kind of a generic upload-everything function. If the file extension is supported it will upload it....
 *  That can be dangerous. Don't want to create a file-sharing network using the games bandwidth.. that could be bad.
 *  But yeah.. it will upload anything... at least, it will if the underlying libraries are fully working (glares at self praying the database 'prepared statements' can handle raw binary properly.) 
 */
	if(!admin) {
		std::cout <<  "Well, a non-admin tried to upload a model.. so uhm.. should we let them?! if not, add return here.\n";
	
	} else {
	 std::cout << "File upload initiated\n"; 
	}
	/****************************************************************************************************
	 *   {                                                                                              *
	 *   type                                                                                           *
	 *   filename                                                                                       *
	 *   filecontents                                                                                   *
	 *   }                                                                                              *
	 ****************************************************************************************************/
	std::string b = in[0];
	std::vector<ulmodel> incoming;
	bool x = false;
	int y = 0;
	for(std::string t=non_safe_string_deserialize(b);
	    t.size()!=0;
	    t=non_safe_string_deserialize(b)) {
	    if(!x) {
		ulmodel tv;
		incoming.push_back(tv);
		incoming[y].filename = t;
	    } else { incoming[y].filecontents = t; ++y; }
	    x=!x;
	}
	std::cout << "uploading " << incoming.size() << " Files.\n";
	insert_ulmodels_into_db(incoming);
}

