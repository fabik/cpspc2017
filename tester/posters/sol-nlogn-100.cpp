#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

#define mp(x,y) make_pair(x, y)
#define For(i, n) for (int i = 0; i < (int) n; i++)

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> pii;

struct node {
    ll length;
    ll begin, end;
    ll open, sum;
    ll openlazy, sumlazy;
    node *left, *right;

    node(node* orig); 

    node(ll bbeg, ll eend, node* lleft, node* rright);
};

map<ll, ll> compress;
node* def_node;
vector<node*> nodes;
vector<ll> decompress;

node::node(ll bbeg, ll eend, node* lleft, node* rright) :
    length(eend - bbeg), begin(bbeg), end(eend), open(0), sum(0), openlazy(0), sumlazy(0), left(lleft), right(rright) {nodes.push_back(this);}

node::node(node* orig) : 
    length(orig->length), begin(orig->begin),
    end(orig->end), open(orig->open),
    sum(orig->sum), openlazy(orig->openlazy),
    sumlazy(orig->sumlazy), left(orig->left), 
    right(orig->right) {nodes.push_back(this);}

node* construct(ll first, ll last) {
    if (first == last) return def_node;
    node *left = nullptr, *right = nullptr;
    if (last - first > 1) {
        left = construct(first, (first + last) / 2);
        right = construct((first + last) / 2, last);
    }
    return new node(decompress [first], decompress [last], left, right);
}

node* update(node* curnode, ll x, ll y1, ll y2, ll mod) {
    if (y1 <= curnode->begin && y2 >= curnode->end) {
        node* newnode = new node(curnode);
        newnode->sum -= x * mod * newnode->length;
        newnode->open += mod * newnode->length;
        newnode->openlazy += mod;
        newnode->sumlazy -= mod * x;

        return newnode;
    }
    else if (y1 < curnode->end && y2 > curnode->begin) {
        node  *left = update(curnode->left, x, y1, y2, mod),
              *right = update(curnode->right, x, y1, y2, mod);

        node* newnode = new node(curnode);
        newnode->sum = left->sum + right->sum + curnode->sumlazy * newnode->length;
        newnode->open = left->open + right->open + curnode->openlazy * newnode->length;
        newnode->left = left;
        newnode->right = right;

        return newnode;
    }
    return curnode;
}

pii fetch(node* curnode, ll y1, ll y2, ll sumlazy, ll openlazy) {
//    cerr << "Fetch " << y1 << ' ' << y2 << ' ' << curnode->begin << ' ' << curnode->end << ' ' << sumlazy << ' ' << openlazy << endl;
    if (y1 <= curnode->begin && y2 >= curnode->end) {
        return mp(curnode->sum + sumlazy * curnode->length,curnode->open + openlazy * curnode->length);
    }

    else if (y1 < curnode->end && y2 > curnode->begin) {
        if (curnode->left == nullptr) {
            ll realsum = curnode->sum + curnode->length * sumlazy;
            ll realopen = curnode->open + curnode->length * openlazy;
            ll intersect = min(y2, curnode->end) - max(y1, curnode->begin);
//            cerr << "Magic result " << curnode->length << ' ' << intersect << ' ' << realsum << ' ' << realopen << endl;
            return mp(realsum / curnode->length * intersect, realopen / curnode->length * intersect);
        }
        else {
            pii leftv = fetch(curnode->left, y1, y2, sumlazy + curnode->sumlazy, openlazy + curnode->openlazy);
            pii rightv = fetch(curnode->right, y1, y2, sumlazy + curnode->sumlazy, openlazy + curnode->openlazy);
            return mp(leftv.first + rightv.first, leftv.second + rightv.second);
        }
    }

    return mp(0, 0);
}

int main () {

    def_node = new node(-1000, -1000, nullptr, nullptr);
    srand(time(NULL) + getpid());

    ll r, c, n, q, MOD;
    cin >> r >> c >> n >> q >> MOD;
    decompress = {0, 1023456789};
    vector<pair<pii, pii> > events;
    For(i, n) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        if (y1 < 0 || x1 < 0 || x1 > r || y2 > c || x1 == x2 || y1 == y2) {
            cerr << "BAD INPUT A! " << i << "\n";
            return 1;
        }
        decompress.push_back(y1);
        decompress.push_back(y2);
        events.push_back(mp(mp(x1, 1), mp(y1, y2)));
        events.push_back(mp(mp(x2, -1), mp(y1, y2)));
    }
    sort(decompress.begin(), decompress.end());
    decompress.resize(int(unique(decompress.begin(), decompress.end()) - decompress.begin()));

    For(i, decompress.size()) {
        compress [decompress [i]] = i;
    }

    map<ll, node*> roots;
    roots [0] = construct(0, decompress.size() - 1);
 

    sort(events.begin(), events.end());
    for(auto& event : events) {
        ll last = (--(roots.end()))->first;
        roots[event.first.first] = update( roots[last], event.first.first, event.second.first, event.second.second, event.first.second);
    }

    ll lastres = 0;

    For(i, q) {
        ll x1, y1, x2, y2, mod;
        cin >> x1 >> y1 >> x2 >> y2 >> mod;
        mod = ((mod % MOD) * (lastres % MOD)) % MOD;

        x1 = (x1 + mod) % MOD; y1 = (y1 + mod) % MOD; x2 = (x2 + mod) % MOD; y2 = (y2 + mod) % MOD;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        if (y1 < 0 || x1 < 0 || x1 > r || y2 > c || x1 == x2 || y1 == y2) {
            cerr << "BAD INPUT B! " << i << "\n";
            return 1;
        }

//        cerr << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
        ll startx = (--(roots.upper_bound(x1)))->first;
        ll endx = (--(roots.upper_bound(x2)))->first;
        pii left = fetch(roots[startx], y1, y2, 0, 0);
        pii right = fetch(roots[endx], y1, y2, 0, 0);

//        cerr << left.first << ' ' << left.second << ' ' << right.first << ' ' << right.second << endl;

        ll leftres = x1 * left.second + left.first;
        ll rightres = x2 * right.second + right.first;
//        cerr << leftres << ' ' << rightres << endl;
        lastres = rightres - leftres;
        printf("%lld\n", lastres);
    }

    for(auto ptr : nodes) delete ptr;
}
