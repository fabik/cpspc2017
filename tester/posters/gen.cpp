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
ll r, c, n, q;

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
    if (y1 <= curnode->begin && y2 >= curnode->end) {
        return mp(curnode->sum + sumlazy * curnode->length,curnode->open + openlazy * curnode->length);
    }

    else if (y1 < curnode->end && y2 > curnode->begin) {
        if (curnode->left == nullptr) {
            ll realsum = curnode->sum + curnode->length * sumlazy;
            ll realopen = curnode->open + curnode->length * openlazy;
            ll intersect = min(y2, curnode->end) - max(y1, curnode->begin);
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

ll myrand() {
    return (((ll)rand()) << 31) + (ll) rand();
}

// Transpose the simple representation
vector<ll> trans(vector<ll> input) {
    For(i, input.size() / 2) swap(input[2*i], input[2*i + 1]);
    return input;
}

// Generate rectangles in several row ranges independently.
vector<ll> strip(ll rmin, ll cmin, ll rmax, ll cmax, ll n) {
    vector<ll> result;
    ll rrange = rmax - rmin + 1;
    ll crange = cmax - cmin + 1;
    ll side = ((ll)sqrt(n) + 1) ;
    ll perr = rrange / side;
    
    For(i, side) {
        ll myn = min(side, n);
        vector<ll> sizes, sizes_blank;

        ll total = 0;
        // Generate sizes in the strip with pseudoexponential distribution
        ll remaining = crange / 2 - 2*myn;
        For(j, myn) {
            n --;
            ll next = 0;
            while (next == 0) next = myrand() % remaining + myrand() % 2 + 1;
            total += next;
            remaining -= next - 2;
            sizes.push_back(next);
        }
        
        // Same with gaps
        remaining = crange - total;
        For(j, sizes.size()) {
            if (remaining == 0) {
                sizes_blank.push_back(0);
                continue;
            }
            ll next = myrand() % remaining;
            remaining -= next;
            sizes_blank.push_back(next);
        }
        random_shuffle(sizes.begin(), sizes.end());
        random_shuffle(sizes_blank.begin(), sizes_blank.end());
        ll curc = 0;
        For(j, sizes.size()) {
            curc += sizes_blank [j];
            ll a = myrand() % perr, b = myrand() % perr;
            while (a == b) a = myrand() % perr;

            result.push_back(a + i * perr + rmin);
            result.push_back(curc + cmin);
            result.push_back(b + i * perr + rmin);
            curc += sizes [j];
            result.push_back(curc + cmin);
        }
    }
    return result;
}

// Generate rectangles in simple checkerboard.
vector<ll> checkerboard(ll rmin, ll cmin, ll rmax, ll cmax, ll n) {
    vector<ll> result;
    ll rrange = rmax - rmin + 1;
    ll crange = cmax - cmin + 1;
    ll side = (sqrt(n) + 1) * 15 / 10;
    ll perr = rrange / side;
    ll perc = crange / side;

    For(i, side) {
        for(ll j = i % 2; j < side; j+= 2) {
            ll a = myrand() % perr, b = myrand() % perc, c = myrand() % perr, d = myrand() % perc;
            while (a == c) a = myrand() % perr;
            while (b == d) b = myrand() % perc;

            n --;
            result.push_back(a + rmin + i*perr);
            result.push_back(b + cmin + j*perc);
            result.push_back(c + rmin + i*perr);
            result.push_back(d + cmin + j*perc);
            if (n <= 0) break;
        }
        if (n <= 0) break;
    }
    return result;
}

vector<ll> unsortable(ll rmin, ll cmin, ll rmax, ll cmax, ll n) {
    n -= n % 4;
    if (n == 0) return vector<ll>();
    ll rrange = rmax - rmin + 1;
    ll crange = cmax - cmin + 1;
    ll rside = 2 * rrange / n;
    ll cside = 2 * crange / n;
    vector<ll> result = unsortable (rmin + rside + 1, cmin + cside + 1, rmax - rside - 1, cmax - cside - 1, n - 4);

    result.push_back(rmin); result.push_back(cmin); result.push_back(rmax - rside - 1); result.push_back(cmin + cside);
    result.push_back(rmax - rside); result.push_back(cmin); result.push_back(rmax); result.push_back(cmax - cside - 1);
    result.push_back(rmin + rside + 1); result.push_back(cmax - cside); result.push_back(rmax); result.push_back(cmax);
    result.push_back(rmin); result.push_back(cmin + cside + 1); result.push_back(rmin + rside); result.push_back(cmax);
    return result;
}

// Create posters along  a rectangle to produce queries with many intersections
vector<ll> intersect(ll n) {
    ll strips = 1 + n / 4;
    ll rlen = r / strips;
    ll clen = c / strips;
    ll rdif = (rlen - 2) / 5;
    ll cdif = (clen - 2) / 5;

    vector<ll> result;

    For(i, strips) {
        result.push_back(myrand() % rdif); result.push_back(i*clen + (myrand() % cdif)); result.push_back(rlen - (myrand() % rdif) - 1); result.push_back((i+1)*clen - (myrand() % cdif) - 1);
        result.push_back(r - rlen + myrand() % rdif); result.push_back(i*clen + (myrand() % cdif)); result.push_back(r - (myrand() % rdif)); result.push_back((i+1)*clen - (myrand() % cdif) - 1);
        if (i > 0 && i < strips - 1) {
            result.push_back(i*rlen + (myrand() % rdif)); result.push_back(myrand() % cdif); result.push_back((i+1)*rlen - (myrand() % rdif) - 1); result.push_back(clen - (myrand() % cdif));
            result.push_back(i*rlen + (myrand() % rdif)); result.push_back(c - clen + (myrand() % cdif)); result.push_back((i+1)*rlen - (myrand() % rdif) - 1); result.push_back(c - (myrand() % cdif));
        }
    }
    return result;
}

vector<ll> intersect_queries(ll n, ll q) {
    ll strips = 1 + n / 4;
    ll rlen = r / strips;
    ll clen = c / strips;
    ll rdif = (rlen - 2) / 5;
    ll cdif = (clen - 2) / 5;

    vector<ll> result;

    For(i, q) {
        ll xb = rdif + myrand() % (rlen - 2*rdif - 3) + 1, xe = rdif + myrand() % (rlen - 2*rdif - 3) + 1;
        ll yb = cdif + myrand() % (clen - 2*cdif - 3) + 1, ye = cdif + myrand() % (clen - 2*cdif - 3) + 1;

        result.push_back(xb); result.push_back(yb); result.push_back(r - xe); result.push_back(c - ye);
    }
    return result;
}

vector<ll> quadrants(ll n) {
    vector<ll> res = checkerboard(0, 0, r/2, c/2, n/3);
    for (ll e : checkerboard(r/2, c/2, r, c, n/3)) res.push_back(e);
    for (ll e : strip(0, c/2, r/2, c, n/6)) res.push_back(e);
    for (ll e : trans(strip(0, r/2, c/2, r, n/6))) res.push_back(e);
    return res;
}

int main () {

    def_node = new node(-1000, -1000, nullptr, nullptr);

    string mode, onlinemode;

    // As in: 1/letzero_chance is the chance of letting a zero-answer-query get to the output
    ll letzero_chance = 50;
    ll MOD, seed;
    cin >> mode >> onlinemode >> r >> c >> n >> q >> MOD >> seed;
    srand(seed);
    decompress = {0, 1023456789};
    vector <ll> rects;
    
    if (mode == "quadrants") {
        rects = quadrants(n);
    }
    else if (mode == "strips") {
        rects = strip(0, 0, r, c, n);
    }
    else if (mode == "rstrips") {
        rects = trans(strip(0, 0, c, r, n));
    }
    else if (mode == "checker") {
        rects = checkerboard(0, 0, r, c, n);
    }
    else if (mode == "unsortable") {
        rects = unsortable(0, 0, r, c, n);
    }
    else if (mode == "intersect") {
       rects = intersect(n);
    }
    n = rects.size() / 4;

    // Random shuffle of the input rectangles
    vector<ll> shuffle(n);
    For(i, n) shuffle [i] = i;
    random_shuffle(shuffle.begin(), shuffle.end());

    printf("%lld %lld %lld %lld %lld\n", r, c, n, q, MOD);

    vector<pair<pii, pii> > events;
    For(i, rects.size() / 4) {
        ll pos = shuffle [i];
        ll x1 = rects[4*pos], y1 = rects[4*pos + 1], x2 = rects[4*pos + 2], y2 = rects[4*pos + 3];
        printf("%lld %lld %lld %lld\n", x1, y1, x2, y2);
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
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

    vector<ll> queries;
    if (mode == "intersect") {
        queries = intersect_queries(n, q);
    }
    else {
        queries = checkerboard(0, 0, r, c, q/4);
        for (ll e : strip(0, 0, r, c, q/4)) queries.push_back(e);
        for (ll e : trans(strip(0, 0, c, r, q/4))) queries.push_back(e);

        while ((ll) queries.size() != 4*q) {
            ll x1 = myrand() % r, y1 = myrand() % c, x2 = myrand() % r, y2 = myrand() % c;
            while (x1 == x2) x1 = myrand() % r;
            while (y1 == y2) y1 = myrand() % c;
            queries.push_back(x1);
            queries.push_back(y1);
            queries.push_back(x2);
            queries.push_back(y2);
        }
    }

    shuffle.clear();
    For(i, q) shuffle.push_back(i);
    random_shuffle(shuffle.begin(), shuffle.end());

    For(i, q) {
        ll x1, y1, x2, y2, mod;
        ll pos = shuffle [i];
        x1 = queries [pos * 4]; y1 = queries [pos * 4 + 1]; x2 = queries [pos * 4 + 2]; y2 = queries [pos * 4 + 3];

        if (onlinemode == "online") mod = myrand() % MOD;
        else mod = 0;
        ll prodmod = (mod * (lastres % MOD)) % MOD;

        ll redo_offline = 0;

        do {
            if (x1 == x2) cerr << "Aaaa!\n";
            if (y1 == y2) cerr << "Aaaa!\n";
            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);

            ll startx = (--(roots.upper_bound(x1)))->first;
            ll endx = (--(roots.upper_bound(x2)))->first;
            pii left = fetch(roots[startx], y1, y2, 0, 0);
            pii right = fetch(roots[endx], y1, y2, 0, 0);

            ll leftres = x1 * left.second + left.first;
            ll rightres = x2 * right.second + right.first;
            lastres = rightres - leftres;
            redo_offline = myrand() % letzero_chance;
            if (lastres == 0 && (onlinemode == "online" || redo_offline != 0)) {
                x1 = myrand() % (r + 1); y1 = myrand() % (c + 1); x2 = myrand() % (r + 1); y2 = myrand() % (c + 1);
                while(x1 == x2) x1 = myrand() % r;
                while(y1 == y2) y1 = myrand() % c;
            }
        } while (lastres == 0 && (onlinemode == "online" || redo_offline != 0));

        ll x1_ = (x1 - prodmod + MOD) % MOD, y1_ = (y1 - prodmod + MOD) % MOD, x2_ = (x2 - prodmod + MOD) % MOD, y2_ = (y2 - prodmod + MOD) % MOD;

        if (rand() % 2 == 1) swap(x1_, x2_);
        if (rand() % 2 == 1) swap(y1_, y2_);

        printf("%lld %lld %lld %lld %lld\n", x1_, y1_, x2_, y2_, mod);
        
    }

    for(auto ptr : nodes) delete ptr;
}
