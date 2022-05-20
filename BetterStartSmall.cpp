#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define FOR(i, a, b) for(int i = (a); i <= (b); i++)
#define REP(n) FOR(O, 1, (n))
#define pb push_back
#define f first
#define s second
typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 100100;

void setIO(string s)
{
    FAST_IO;
    freopen((s+".in.txt").c_str(), "r", stdin);
    freopen((s+".out.txt").c_str(), "w", stdout);
}

void setIO(string s, bool in)
{
    FAST_IO;
    if (in)
        freopen((s+".in.txt").c_str(), "r", stdin);
    else
        freopen((s+".out.txt").c_str(), "r", stdin);
}

struct skill {
    string name;
    int level;
};

struct contributor {
    string name;
    int skillNumber;
    vector<skill> skills;
    map<string, int> skillNameToId;

    void increaseSkill (string name) {
        if (skillNameToId.find(name) != skillNameToId.end()) {
            int id = skillNameToId[name];
            skills[id].level++;
        } else {
            skillNameToId[name] = ((int)skills.size());
            skill newSkill;
            newSkill.name = name;
            newSkill.level = 1;
            skills.pb(newSkill);
        }
    }

    int getSkillLevel (string name) {
        if (skillNameToId.find(name) != skillNameToId.end()) {
            int id = skillNameToId[name];
            return skills[id].level;
        } else {
            return 0;
        }
    }
};

struct project{
    string name;
    int days, score, bestBefore, rolesNumber;
    vector<skill> requiredRoles;
};

int c, p;
vector<contributor> people;
vector<project> projects;
map<string, int> peopleNameToId, projectNameToId;

void readInput () {
    cin >> c >> p;
    people.resize(c);
    projects.resize(p);

    for (int i = 0; i < c; i++) {
        cin >> people[i].name >> people[i].skillNumber;
        peopleNameToId[people[i].name] = i;
        for (int jj = 0; jj < people[i].skillNumber; jj++) {
            skill curSkill;
            cin >> curSkill.name >> curSkill.level;
            people[i].skills.push_back(curSkill);
            people[i].skillNameToId[curSkill.name] = jj;
        }
    }

    for (int i = 0; i < p; i++) {
        cin >> projects[i].name >> projects[i].days >> projects[i].score >> projects[i].bestBefore >> projects[i].rolesNumber;
        projectNameToId[projects[i].name] = i;
        for (int jj = 0; jj < projects[i].rolesNumber; jj++) {
            skill reqSkill;
            cin >> reqSkill.name >> reqSkill.level;
            projects[i].requiredRoles.push_back(reqSkill);
        }
    }
}

int e;
vector<int> completedProjects;
bool projectTaken[MAXN];
//set<string> testForSimilar;
vector<vector<int>> assignedRoles;

void readOutput () {
    //freopen((s+".out.txt").c_str(), "w", stdout);
    cin >> e;
    completedProjects.resize(e);
    assignedRoles.resize(e);

    for (int i = 0; i < e; i++) {
        string s; cin >> s;

        int id = projectNameToId[s];
        
        completedProjects[i] = id;
        if (projectTaken[id]) {

            cerr << " In the output file project with name = " << projects[id].name << " is mentioned more than once" << endl;
            exit(0);
        }

        projectTaken[id] = true;
        int peopleInProject = projects[id].rolesNumber;
        assignedRoles[i].resize(peopleInProject);

        for (int jj = 0; jj < peopleInProject; jj++) {
            string name;
            cin >> name;
            int personId = peopleNameToId[name];
            assignedRoles[i][jj] = personId;
        }
    }

}

int minTime[MAXN];

// people, projects, peopleNameToId ir  projectNameToId -- globalus kintamieji

int calcScore (vector<vector<int>> assignedRoles, vector<int> completedProjects) {
    int e = completedProjects.size();
    int score = 0;

    for (int ii = 0; ii < e; ii++) {
        int i = completedProjects[ii];
        project thisProject = projects[i];

        int startTime = 0;
        int roleCnt = (int)assignedRoles[ii].size();
        map<string, int> curSkills;
        for (int j = 0; j < roleCnt; j++) {
            int personId = assignedRoles[ii][j];
            for (skill sk : people[personId].skills) {
                curSkills[sk.name] = max(curSkills[sk.name], sk.level);
            }
            string skillName = thisProject.requiredRoles[j].name;
            int requiredLevel = thisProject.requiredRoles[j].level;
            int personsLevel = people[personId].getSkillLevel(skillName);
            if(personsLevel < requiredLevel - 1) {
                cerr << "Person " << people[personId].name << " has too low skill for the task " << i << "\n";
                exit(0);
            }
            startTime = max(minTime[personId], startTime);
        }
        
        int durationTime = thisProject.days;
        int endTime = startTime + durationTime-1;
        int bestBefore = thisProject.bestBefore;
        int defaultScore = thisProject.score;

        int sc = max(0, defaultScore - max(0, endTime - bestBefore));


        for (int j = 0; j < roleCnt; j++) {
            int personId = assignedRoles[ii][j];
            string skillName = thisProject.requiredRoles[j].name;
            int requiredLevel = thisProject.requiredRoles[j].level;
            int personsLevel = people[personId].getSkillLevel(skillName);
            int maxLevel = curSkills[skillName];
            if(maxLevel < requiredLevel) {
                cerr << "No mentor found for skill " << skillName << "\n";
                exit(0);
            }
            minTime[assignedRoles[ii][j]] = endTime + 1;
            if(requiredLevel <= personsLevel) {
                people[personId].increaseSkill(skillName);
            }
        } 
        score += sc;
    }
    return score;
}

int main()
{
    FAST_IO;
    //setIO("A");
    setIO("A", true);
    readInput();

    setIO("A", false);
    readOutput();
    int score = calcScore (assignedRoles, completedProjects);

    cerr << " score: " << score << endl;

    return 0;
}
