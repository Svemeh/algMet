/**
 *   Hovedrisset til oblig nr 2.
 *
 *   For programmets funksjonalitet se:  Oblig2.pdf
 *
 *   @file    OBLIG2.CPP
 *   @author  Frode Haug, NTNU
 */


#include <iostream>             //  cout
using namespace std;


/**
 *  Node (med ID/key/data og venstre/høyre pekere til nodens barn).
 */
struct Node {
    int ID;                 //  Nodens ID/key/nøkkel/navn (et tall).
    Node *left, *right;     //  Peker til begge subtrærne (evt. 'nullptr').
    Node(int id) { ID = id;  left = right = nullptr; }
};


Node* gRoot1 = nullptr, *gRoot2 = nullptr; ///< 2x rot-pekere
                                   // (har altså ikke at  head->right er rota)
Node* byggTre();
void  settAlleIDerLike(Node* t);
bool  erTrerneIdentiske(Node* t1, Node* t2);    //  Oppgave A
bool  erTreetSymmetrisk(Node* t1, Node* t2);    //  Oppgave B


/**
 *  Hovedprogrammet:
 */
int main() {
    gRoot1 = byggTre();     gRoot2 = byggTre();

//  Tester 3A - To identiske trær:
    cout << "\n\nBegge trærne er "
       << (!erTrerneIdentiske(gRoot1, gRoot2) ? "IKKE " : "") << "identiske.";

//  Tester 3A - To ikke-identiske trær:
    delete gRoot2->right->right->left;     //  Sletter nr.10 i tre nr.2
    gRoot2->right->right->left = nullptr;
    cout << "\n\nBegge trærne er "
       << (!erTrerneIdentiske(gRoot1, gRoot2) ? "IKKE " : "") << "identiske.";

//  Tester 3A - To identiske trær igjen:
    delete gRoot1->right->right->left;     //  Sletter nr.10 også i tre nr.1
    gRoot1->right->right->left = nullptr;
    cout << "\n\nBegge trærne er "
       << (!erTrerneIdentiske(gRoot1, gRoot2) ? "IKKE " : "") << "identiske.";

//  Tester 3B - Treet er IKKE symmetrisk:
    cout << "\n\nTreet er "
       << (!erTreetSymmetrisk(gRoot1, gRoot1) ? "IKKE " :"") << "symmetrisk.";

//  Tester 3B - Treet er IKKE symmetrisk:
    delete gRoot1->right->right->right;       //  Sletter nr.11 i tre nr.1
    gRoot1->right->right->right = nullptr;
                                   //  Trærne er strukturmessig symmetriske,
    cout << "\n\nTreet er "        //     men IDene er ikke det.
       << (!erTreetSymmetrisk(gRoot1, gRoot1) ? "IKKE " :"") << "symmetrisk.";

//  Tester 3B - Treet er symmetrisk:
    settAlleIDerLike(gRoot1); // Setter alle IDene like, derfor nå symmetrisk.
    cout << "\n\nTreet er "
       << (!erTreetSymmetrisk(gRoot1, gRoot1) ? "IKKE " :"") << "symmetrisk.";

    cout << "\n\n\n";
    return 0;
}


/**
 *  Bygger et binært testtre.
 *
 *  @return   Peker til rota i treet som er bygd
 */
Node* byggTre() {
    Node* p[12];
    for (int i = 1; i <= 11; i++)  p[i] = new Node(i); //  Bygger treet:   //
    p[1]->left = p[2];    p[1]->right = p[3];  //            1             //
    p[2]->left = p[4];    p[2]->right = p[5];  //        /       \         //
    p[3]->left = p[6];    p[3]->right = p[7];  //       2         3        //
    p[5]->left = p[8];                         //     /   \     /   \      //
                          p[6]->right = p[9];  //    4     5   6     7     //
    p[7]->left = p[10];   p[7]->right = p[11]; //         /     \   / \    //
    return p[1];                               //        8       9 10 11   //
}


/**
 *  Går igjennom og setter alle treets IDer/keyer til '99'.
 *
 *  @param  t  -  Peker til (sub)treets rot
 */
void settAlleIDerLike(Node* t) {
  if (t) {
      t->ID = 99;
      settAlleIDerLike(t->left);
      settAlleIDerLike(t->right);
  }
}


/**
 *  OPPGAVE A - Finner ut og returnerer om to binære trær er HELT IDENTISKE:
 *
 *  @param   t1  -  Peker til (sub)tre nr.1
 *  @param   t2  -  Peker til (sub)tre nr.2
 *  @return  Om de to (sub)trærne er HELT identiske eller ei
 */
bool erTrerneIdentiske(Node* t1, Node* t2) {
    // hvis en er nullptr, returner true(Identiske) hvis begge er nullptr
    if (!(t1 && t2)) return t1 == t2;   

    // Ulike ID-er, dermed IKKE Identiske
    if (t1->ID != t2->ID) return false;

    return erTrerneIdentiske(t1->left, t2->left) 
        && erTrerneIdentiske(t1->right, t2->right);
}


/**
 *  OPPGAVE B - Finner ut og returnerer om et binært tre er TOTALT SYMMETRISK:
 *
 *  @param   t1  -  Peker til (sub)tre nr.1
 *  @param   t2  -  Peker til (sub)tre nr.2
 *  @return  Om de totaltreet er symmetrisk omkring/under rota eller ei
 */
bool erTreetSymmetrisk(Node* t1, Node* t2) {
    // hvis en er nullptr, returner true(Symmetriske) hvis begge er nullptr
    if (!(t1 && t2)) return t1 == t2;   
    // linjen over kunne blitt skrevet som:
    //      if (!t1 && !t2)  return true;
    //      if (!t1 || !t2) return false;

    // Ulike ID-er, dermed IKKE symmetrisk
    if (t1->ID != t2->ID) return false;
    
    // rekursjons-steget    -   preorder
    return erTreetSymmetrisk(t1->left, t2->right)
        && erTreetSymmetrisk(t1->right, t2->left);
}