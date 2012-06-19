#ifndef COMMAND_HPP
#define COMMAND_HPP
//test2
/*
 *  command.h
 *  
 *
 *  Created by Pat Schloss on 10/23/08.
 *  Copyright 2008 Patrick D. Schloss. All rights reserved.
 *
 */

/*This class is a parent to all the command classes.  */


#include "mothur.h"
#include "optionparser.h"
#include "validparameter.h"
#include "mothurout.h"
#include "commandparameter.h"


class Command {
	
	public:
		Command() {  m = MothurOut::getInstance();   } 
		
		//needed by gui
		virtual string getCommandName() = 0;
		virtual string getCommandCategory() = 0;
		virtual string getHelpString() = 0;
		virtual string getCitation() = 0;
		virtual string getDescription() = 0;
		
		virtual map<string, vector<string> > getOutputFiles() { return outputTypes; }
        virtual string getOutputFileNameTag(string, string) = 0;  //we may not know the complete filename, because some commands use info from the file to create the output file name (ie label). but we do the ending tag which should be enough to find the output file name from a list. Allows for optional passing of the inputFileName for the commands that require its extension.
		virtual vector<string> setParameters() = 0; //to fill parameters
		virtual vector<CommandParameter> getParameters() { return parameters; }
	
		virtual int execute() = 0;
		virtual void help() = 0;
		void citation() { m->mothurOutEndLine(); m->mothurOut(getCitation()); m->mothurOutEndLine(); }
		virtual ~Command() { }
	
	protected:
		MothurOut* m;
		bool calledHelp;
			
		map<string, vector<string> > outputTypes;
		vector<CommandParameter> parameters;
	
		map<string, vector<string> >::iterator itTypes;
};

#endif
