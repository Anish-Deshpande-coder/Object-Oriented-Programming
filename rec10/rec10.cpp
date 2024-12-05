#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const = 0;  // Abstract method for testing
    virtual void play() const = 0;       // Abstract method for orchestra performance
    virtual ~Instrument() {}

protected:
    virtual void display(ostream& os) const = 0;  // For MILL output
private:
    friend ostream& operator<<(ostream& os, const Instrument& instr) {
        instr.display(os);
        return os;
    }
};

// Brass instruments
class Brass : public Instrument {
public:
    Brass(unsigned size) : mouthpieceSize(size) {}

    void makeSound() const {
        cout << "To make a sound... blow on a mouthpiece of size " << getMouthpieceSize() << endl;
    }

protected:
    unsigned getMouthpieceSize() const { return mouthpieceSize; }

private:
    unsigned mouthpieceSize;
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned size) : Brass(size) {}

    void play() const { cout << "Toot"; }

protected:
    void display(ostream& os) const { os << "Trumpet: " << getMouthpieceSize(); }
};

class Trombone : public Brass {
public:
    Trombone(unsigned size) : Brass(size) {}

    void play() const { cout << "Blat"; }

protected:
    void display(ostream& os) const { os << "Trombone: " << getMouthpieceSize(); }
};

// String instruments
class String : public Instrument {
public:
    String(unsigned pitch) : pitch(pitch) {}

    void makeSound() const {
        cout << "To make a sound... bow a string with pitch " << getPitch() << endl;
    }

protected:
    unsigned getPitch() const { return pitch; }

private:
    unsigned pitch;
};

class Violin : public String {
public:
    Violin(unsigned pitch) : String(pitch) {}

    void play() const { cout << "Screech"; }

protected:
    void display(ostream& os) const { os << "Violin: " << getPitch(); }
};

class Cello : public String {
public:
    Cello(unsigned pitch) : String(pitch) {}

    void play() const { cout << "Squawk"; }

protected:
    void display(ostream& os) const { os << "Cello: " << getPitch(); }
};

// Percussion instruments
class Percussion : public Instrument {
public:
    void makeSound() const { cout << "To make a sound... hit me!" << endl; }
};

class Drum : public Percussion {
public:
    void play() const { cout << "Boom"; }

protected:
    void display(ostream& os) const { os << "Drum"; }
};

class Cymbal : public Percussion {
public:
    void play() const { cout << "Crash"; }

protected:
    void display(ostream& os) const { os << "Cymbal"; }
};

// Musical Instrument Lending Library
class MILL {
public:
    void receiveInstr(Instrument& instr) {
        instr.makeSound();
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] == nullptr) {
                inventory[i] = &instr;
                return;
            }
        }
        inventory.push_back(&instr);
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i]) {
                Instrument* instr = inventory[i];
                inventory[i] = nullptr;
                return instr;
            }
        }
        return nullptr;
    }

    void dailyTestPlay() const {
        for (const Instrument* instr : inventory) {
            if (instr) instr->makeSound();
        }
    }

private:
    vector<Instrument*> inventory;

    friend ostream& operator<<(ostream& os, const MILL& mill) {
        os << "The MILL has the following instruments: ";
        bool any = false;
        for (const Instrument* instr : mill.inventory) {
            if (instr) {
                os << "\n\t" << *instr;
                any = true;
            }
        }
        if (!any) os << "None";
        return os;
    }
};

// Musician class provided
class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << name << " has no instr\n";
    }

    void play() {
        if (instr) instr->play();
    }

private:
    Instrument* instr;
    string name;
};

// Orchestra class
class Orch {
public:
    void addPlayer(Musician& musician) {
        orchestra.push_back(&musician);
    }

    void play() const {
        for (Musician* musician : orchestra) {
            musician->play();
            cout << " ";
        }
        cout << endl;
    }

private:
    vector<Musician*> orchestra;
};

// Main function
int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

     groucho.testPlay();
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();
     harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}
