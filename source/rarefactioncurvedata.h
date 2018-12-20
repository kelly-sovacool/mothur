#ifndef RAREFACTIONCURVEDATA_H
#define RAREFACTIONCURVEDATA_H

#include "mothur.h"
#include "sabundvector.hpp"
#include "display.h"
#include "observable.h"

/***********************************************************************/
//Has a display for each calculator
class RarefactionCurveData : public Observable {
	
public:
	RarefactionCurveData() : rank(0) {};
	
	void registerDisplay(Display* o)            {	displays.insert(o);				}
    void registerDisplays(vector<Display*> o)	{	for(int i=0;i<o.size();i++){ registerDisplay(o[i]); 	} }
    
	void updateRankData(SAbundVector* rv)       {	rank = rv; for(set<Display*>::iterator pos=displays.begin();pos!=displays.end();pos++){ (*pos)->update(rank); } 	}

private:
	set<Display*> displays;
	SAbundVector* rank;
	
};

/***********************************************************************/

class SharedRarefactionCurveData : public Observable {
	
public:
	SharedRarefactionCurveData() {}; //: shared1(0), shared2(0) 
	
	void registerDisplay(Display* o)            {	displays.insert(o);				}
    void registerDisplays(vector<Display*> o)	{	for(int i=0;i<o.size();i++){ registerDisplay(o[i]); 	} }
	
	void updateSharedData(vector<SharedRAbundVector*> r, int numSeqs, int numGroupComb)	{
        shared = r; NumSeqs = numSeqs; NumGroupComb = numGroupComb;
        groups.clear(); for (int i = 0; i < r.size(); i++) { groups.push_back(r[i]->getGroup()); }
        SharedDataChanged();
    }
	
private:
	set<Display*> displays;
	vector<SharedRAbundVector*> shared;
	int NumSeqs, NumGroupComb;
    vector<string> groups;
    
    void SharedDataChanged()                    {	for(set<Display*>::iterator pos=displays.begin();pos!=displays.end();pos++){ (*pos)->update(shared, NumSeqs, NumGroupComb, groups); }				}
	
};

/***********************************************************************/


#endif

