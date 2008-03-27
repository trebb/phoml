#include "CBoreside_alignement.h"

#include <fstream>
#include <sstream>

#include "transformation.h"
#include "..//Basics//Matrix//matrix.h"
#include "..//Basics//point.h"

CBoreside_alignement::CBoreside_alignement(string &KooDat1,string &KooDat2)
{
	 //ini	
	 m_is_ok=true;	
		
	 //read the koordinaten files	
	 bool test1 = read_KooDat(KooDat1,m_KooList1);
	 if(!test1)
	 {m_is_ok=false;
	  m_error_string+=" Fehler beim auslesen der Koordinaten Datei 1! ";
	 }
	 
	 bool test2 = read_KooDat(KooDat2,m_KooList2);
	 if(!test2)
	 {m_is_ok=false;
	  m_error_string+=" Fehler beim auslesen der Koordinaten Datei 2! ";
	 }
	 	  
	 //merge the to lists after the point numbers 
	 bool test_merge = merge_list(m_KooList1,m_KooList2);
	 if(!test_merge)
	 {m_is_ok=false;
	  m_error_string+=" Fehler beim zusammenstellen der Koordinaten-Listen! ";
	 }
	  
	 //Verbleibene Punkte die für die 3D Helmerttransformation verwendet werden
	 
	 KooL_anzeigen(m_KooList1);
	 KooL_anzeigen(m_KooList2);
	
	
	 //convert to Point Lists
	 list<Point> KooListP1;
	 list<Point> KooListP2;
	 
	 convert_list(m_KooList1,KooListP1);
	 convert_list(m_KooList2,KooListP2);
	
	     //show	 
		 //KooL_anzeigen(KooListP1);
		 //KooL_anzeigen(KooListP2);
     


     //3D Helmerttransformation
     
     list<Point> KoorejectP1,KoorejectP2;
     
     Transformation HT3D(KooListP1,KooListP2,KoorejectP1,KoorejectP2);
     
     cout<<endl<<endl;
     cout<<"R: "<<HT3D.get_Rotation()<<endl;
     cout<<"T: "<<HT3D.get_Translation()<<endl;
     cout<<"m: "<<HT3D.get_Massstab()<<endl;
     
     //Kontrollrechnung 
     list<CPoint_Nr>::iterator iTL1=m_KooList1.begin();
     list<CPoint_Nr>::iterator iTL2=m_KooList2.begin();
  
     while(iTL1!=m_KooList1.end())
     {   
	     Point P2sys1=*(iTL1);
	     Point P2sys2=*(iTL2);
	     
	     Point P2Tsys2=P2sys1.Rotation(HT3D.get_Translation(),HT3D.get_Rotation(),HT3D.get_Massstab());
	     
	     Point P2diff=P2sys2.Subt(P2Tsys2);
	     
	     cout<<endl<<"Diff_Rot:"<<" Pktnr:"<<iTL1->get_PktNr()<<P2diff;
	     
	  ++iTL1;
	  ++iTL2; 
     }
     
     cout<<endl<<"Verwendete Punkte Anzahl: "<< KooListP1.size();

     //Bei fehlenden Punktnummern Zuordnung herstellen
     //in Arbeit -> erstmal nicht wichtig
     
     
     //Position des Fahrzeuges inkl. Drehwinkel
     
     
     //Position der Camera im lokalen Koordinatensystem
     
     
     //Position der Camera im globalen Koordinatensystem berechnen (Transformation)
     
     
	 
	
}

CBoreside_alignement::~CBoreside_alignement()
{
}

bool CBoreside_alignement::read_KooDat(string &KooDat,list<CPoint_Nr> &KooList)
{
 //read
 ifstream DAT_TXT;  
 DAT_TXT.open(KooDat.c_str()); 
 if(!DAT_TXT) { return false; }

 string hilf;
 
 int pkt=0;
 double x=0.0,y=0.0,z=0.0;

 CPoint_Nr T(0,0.0,0.0,0.0);
 
 while(getline(DAT_TXT,hilf))
 {                   
	        //if(line>=m_ibegin_txt_pos_applanix)
			if(hilf.length()>0 )
			if(hilf.at(0)!='#' )
			{
			 stringstream stream; 
			 stream<<hilf.c_str();
			 hilf.erase();
			 stream>>pkt>>x>>y>>z;
			 
			 T.set_PktNr(pkt);
			 T.set_X(x);
			 T.set_Y(y);
			 T.set_Z(z);

			 KooList.push_back(T);			 
			}
 }
 DAT_TXT.close();
 DAT_TXT.clear();
 

 return true;
}

bool CBoreside_alignement::merge_list(list<CPoint_Nr> &KooList1,list<CPoint_Nr> &KooList2)
{
 //merge the two lists so that every point list have the same point numbers, the rest will be del
 
 //sort the two lists after point numbers
 KooList1.sort();
 KooList2.sort();
	 
 
 list<CPoint_Nr>::iterator iKooList1 = KooList1.begin();
 list<CPoint_Nr>::iterator iKooList2 = KooList2.begin();
 
	 //primary list is KooList1
	 while(iKooList1!=KooList1.end())
	 {
          	 	 	
	 	  if(iKooList2==KooList2.end())
	 	  {
	 	   KooList1.erase(iKooList1,KooList1.end());
	 	   break;
	 	  }
	 	  
		  //same number
		  if(iKooList1->get_PktNr()==iKooList2->get_PktNr()) 
		  {
		   ++iKooList1;
		   ++iKooList2;
		  }
		  else if(iKooList1->get_PktNr()<iKooList2->get_PktNr())
		  {
		   KooList1.erase(iKooList1++);
		  }
		  else
		  {
		   KooList2.erase(iKooList2++);
		  }
		  
		  if(iKooList1==KooList1.end())
	 	  {
	 	   KooList2.erase(iKooList2,KooList2.end());
	 	  }
	 }
	 
	 if(KooList1.size()<4)
	 { return false;
	   m_error_string+=" Minimale Anzahl der uebereinstimmenden Punktnummer wurde nicht erreicht! ";
	 }

return true;
}

bool CBoreside_alignement::convert_list(list<CPoint_Nr> &InputList,list<Point> &OutputList)
{
	list<CPoint_Nr>::iterator iInputList=InputList.begin();
	
	while(iInputList!=InputList.end())
	{
	 //Point P(iInputList->get_X(),iInputList->get_Y(),iInputList->get_Z());
	 //Klassen Konvertierung von CPoint _NR zu Point ;-)
	 Point P=*iInputList;
	 OutputList.push_back(P);
	 ++iInputList;
	}
return true;
}


void CBoreside_alignement::KooL_anzeigen(list<CPoint_Nr> &KooList)
{
 list<CPoint_Nr>::iterator iKooList=KooList.begin();

	while(iKooList!=KooList.end())
	{
	 cout<<endl<<*iKooList;
	 ++iKooList;
	}
 cout<<endl;
}

void CBoreside_alignement::KooL_anzeigen(list<Point> &KooList)
{
 list<Point>::iterator iKooList=KooList.begin();

	while(iKooList!=KooList.end())
	{
	 cout<<endl<<*iKooList;
	 ++iKooList;
	}
 cout<<endl;
}
