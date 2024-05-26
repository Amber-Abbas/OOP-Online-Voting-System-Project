#include <iostream>
#include <string>

using namespace std;

class Voter {
private:
    string name;
    bool hasVoted;

public:
    Voter()
    {

    }
    Voter(const string& voterName) {
        name = voterName;
        hasVoted = false;
    }

    string getName() const {
        return name;
    }

    bool getHasVoted() const {
        return hasVoted;
    }

    void setHasVoted(bool voted) {
        hasVoted = voted;
    }
};

class Candidate {
private:
    string name;
    int voteCount;

public:
    Candidate()
    {

    }
    Candidate(const string& candidateName) {
        name = candidateName;
        voteCount = 0;
    }

    string getName() const {
        return name;
    }

    int getVoteCount() const {
        return voteCount;
    }

    void incrementVoteCount() {
        voteCount++;
    }
};

class VotingSystem {
private:
    Candidate* candidates;
    int candidateCount;
    Voter* voters;
    int voterCount;

public:
    VotingSystem(int numCandidates, int numVoters) {
        candidateCount = numCandidates;
        candidates = new Candidate[numCandidates];
        voterCount = numVoters;
        voters = new Voter[numVoters];
    }

    ~VotingSystem() {
        delete[] candidates;
        delete[] voters;
    }

    void addCandidate(int index, const string& name) {
        if (index >= 0 && index < candidateCount) {
            candidates[index] = Candidate(name);
        }
    }

    void addVoter(int index, const string& name) {
        if (index >= 0 && index < voterCount) {
            voters[index] = Voter(name);
        }
    }

    void displayCandidates() const {
        for (int i = 0; i < candidateCount; i++) {
            cout << (i + 1) << ". " << candidates[i].getName() << endl;
        }
    }

    void vote(int voterIndex, int candidateIndex) {
        if (voterIndex >= 0 && voterIndex < voterCount && candidateIndex >= 1 && candidateIndex <= candidateCount) {
            if (!voters[voterIndex].getHasVoted()) {
                candidates[candidateIndex - 1].incrementVoteCount();
                voters[voterIndex].setHasVoted(true);
                cout << "Vote recorded successfully!" << endl;
            }
            else {
                cout << "You have already voted!" << endl;
            }
        }
        else {
            cout << "Invalid voter index or candidate index!" << endl;
        }
    }

    void displayResults() const {
        cout << "Voting Results:" << endl;
        for (int i = 0; i < candidateCount; i++) {
            cout << candidates[i].getName() << ": " << candidates[i].getVoteCount() << " votes" << endl;
        }
    }
};

int main() {
    int candidateCount;
    cout << "Enter the number of candidates: ";
    cin >> candidateCount;

    int voterCount;
    cout << "Enter the number of voters: ";
    cin >> voterCount;

    VotingSystem votingSystem(candidateCount, voterCount);

    cout << "Enter the names of the candidates:" << endl;
    for (int i = 0; i < candidateCount; i++) {
        string name;
        cout << "Candidate " << (i + 1) << ": ";
        cin >> name;
        votingSystem.addCandidate(i, name);
    }

    cout << "Enter the names of the voters:" << endl;
    for (int i = 0; i < voterCount; i++) {
        string name;
        cout << "Voter " << (i + 1) << ": ";
        cin >> name;
        votingSystem.addVoter(i, name);
    }

    cout << endl << "=== Voting Begins ===" << endl;
    cout << "Cast your vote by entering the voter index and candidate index." << endl;

    int voterIndex, candidateIndex;
    do {
        cout << endl << "Candidates:" << endl;
        votingSystem.displayCandidates();
        cout << "Voter Index (Press 0 for result ): ";
        cin >> voterIndex;

        if (voterIndex != 0) {
            cout << "Candidate Index: ";
            cin >> candidateIndex;
            votingSystem.vote(voterIndex - 1, candidateIndex);
        }
    } while (voterIndex != 0);

    cout << endl << "=== Voting Ends ===" << endl;
    cout << "Thank you for voting!" << endl << endl;

    votingSystem.displayResults();

    return 0;
}