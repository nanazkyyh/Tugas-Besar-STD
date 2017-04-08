//
// Created by Ki Ageng Satria Pamungkas on 3/23/17.
//
#include "document.h"
void createlist (docList &L){
	L.first = NULL;
	L.last = NULL;
};

void addDoc (docList &L, infotype x){
	docAddress P = new docElm;
	P->tagsCount = 0;
	P->info = x;
	P->next = NULL;
	P->child.first = NULL;
	P->child.last = NULL;
	if (L.first == NULL){
		L.first = P;
		L.last = P;
	}else {
		L.last->next = P;
		L.last = P;
	};
};

docAddress findElm(docList &L, infotype x){
	docAddress P=L.first;
	while ((P->info != x) and (P->next != NULL)){
		P = P->next;
	}if (P->info == x){
		return P;
	}else {
		return NULL;
	};
};
void createRelation(docList &Ld,tagsList &Lt, infotype x, infotype y){
    docAddress Pd = findElm(Ld,x);
    tagsAddress Pt = findTags(Lt,y);
    Pd->tagsCount+=1;
    Pt->tagsUsed+=1;
    childAddress P = new childElm;
    P->info = Pt;
    if(Pd->child.first == NULL){
        Pd->child.first = P;
        Pd->child.last = P;
    }else{
        Pd->child.last->next =P;
        Pd->child.last = P;
    }
};
void showdoc(docList &L){
	docAddress P=L.first;
	while (P!= NULL){
		cout<<"Document="<<P->info<<endl;
		childAddress Pt = P->child.first;
        cout<<"Tags:"<<endl;
        while (Pt != NULL){
			cout<<"#"<<Pt->info->info<<" ";
			Pt = Pt->next;
		};
		P = P->next;
	};
};
tagsAddress popTag(tagsList &L){
    tagsAddress P = L.first;
    tagsAddress max = P;
    P = P->next;
    while(P != NULL){
        if(P->tagsUsed > max->tagsUsed){
            max = P;
        }
        P = P->next;
    }
    return max;
}
childAddress findTagsInDoc(docAddress doc, infotype x){
    childAddress P = doc->child.first;
    while ((P->info->info != x) and (P->next != NULL)){
        P = P->next;
    }if (P->info->info == x){
        return P;
    }else {
        return NULL;
    };
}
void docPop(docList &dL, tagsList &tL){
	docAddress P = dL.first;
	while(P != NULL){
		if(findTagsInDoc(P,popTag(tL)->info) != NULL){
			cout<<P->info<<endl;
		}
        P = P->next;
	}
}
void deleteDoc(docList &dL,tagsList &tL, infotype x){
    docAddress Pd = findElm(dL,x);
    childAddress dC = Pd->child.first;
    while(dC != NULL){
        dC->info->tagsUsed-=1;
        dC= dC->next;
    }
    if(Pd == dL.first){
        dL.first = Pd->next;
    }else if(Pd == dL.last){
        docAddress dP = dL.first;
        while(dP->next != Pd){
            dP = dP->next;
        }
        dL.last = dP;
        dP->next = Pd->next;
    }else{
        docAddress dP = dL.first;
        while(dP->next != Pd){
            dP = dP->next;
        }
        dP->next = Pd->next;
    }
    delete(Pd);
};
void deleteCertTags(docList &dL,tagsList &tL, infotype x){
    tagsAddress Pt = findTags(tL,x);
    docAddress Pd = dL.first;
    childAddress Pc1,Pc2;
    while(Pd != NULL){
        Pc1 = Pd->child.first;
        if(Pc1->info->info == x){
            Pd->child.first = Pc1->next;
            delete(Pc1);
        }else{
            while(Pc1->next->info->info != x){
                Pc1 = Pc1->next;
            }
            Pc2 = Pc1->next;
            if(Pc2 == Pd->child.last){
                Pd->child.last = Pc1;
            }
            Pc1->next = Pc2->next;
        }
    }
};
tagsAddress smallTag(tagsList &L){
    tagsAddress P = L.first;
    tagsAddress min = P;
    P = P->next;
    while(P != NULL){
        if(P->tagsUsed < min->tagsUsed){
            min = P;
        }
        P = P->next;
    }
    return max;
};
void showSmallTag(docList &dL,tagsList &tL){
    docAddress P = dL.first;
    while(P != NULL){
        if(findTagsInDoc(P,smallTag(tL)->info) != NULL){
            cout<<P->info<<endl;
        }
        P = P->next;
    }
}
void notagDoc(docList &dL){
    docAddress P = dL.first;
    while(P != NULL){
        if(tagsUsed == 0){
            cout<<P.info<<endl;
        }
    }
}