#ifndef CP_TEMPLATES_DEBUG_HPP
#define CP_TEMPLATES_DEBUG_HPP 1

#include <bits/stdc++.h>

#define debug(...) ((void)(cerr << "[" << #__VA_ARGS__ << "] = ", local_debug::multiple_debug_out(__VA_ARGS__), cerr << "\n"))

namespace local_debug {

using namespace std;

template<typename T>
void debug_out(T x);
template<floating_point T>
void debug_out(T x);
void debug_out(bool x);
void debug_out(const string &s);
template<typename T, size_t N>
void debug_out(const array<T, N> &a);
template<typename T>
void debug_out(const vector<T> &v);
template<typename T>
void debug_out(const deque<T> &q);
template<typename T>
void debug_out(stack<T> s);
template<typename T>
void debug_out(queue<T> q);
template<typename T, typename S, typename C>
void debug_out(priority_queue<T, S, C> q);
template<typename T>
void debug_out(const set<T> &s);
template<typename T>
void debug_out(const multiset<T> &s);
template<typename K, typename V>
void debug_out(const map<K, V> &d);
template<typename K, typename V>
void debug_out(const unordered_map<K, V> &d);
template<typename T, typename U>
void debug_out(const pair<T, U> &p);
template<size_t I, typename... Ts>
void debug_out_tuple(const tuple<Ts...> &t);
template<typename... Ts>
void debug_out(const tuple<Ts...> &t);
void multiple_debug_out();
template<typename T, typename... Ts>
void multiple_debug_out(T &&x, Ts &&...args);

template<typename T>
void debug_out(T x) {
    cerr << x;
}

template<floating_point T>
void debug_out(T x) {
    cerr << fixed << setprecision(2) << x;
}

void debug_out(bool x) {
    cerr << boolalpha << x;
}

void debug_out(const string &s) {
    cerr << "\"" << s << "\"";
}

template<typename T, size_t N>
void debug_out(const array<T, N> &a) {
    cerr << "[";
    for (size_t i = 0; i < N; ++i) {
        if (i != 0) cerr << ", ";
        debug_out(a[i]);
    }
    cerr << "]";
}

template<typename T>
void debug_out(const vector<T> &v) {
    size_t n = v.size();
    cerr << "[";
    for (size_t i = 0; i < n; ++i) {
        if (i != 0) cerr << ", ";
        debug_out(v[i]);
    }
    cerr << "]";
}

template<typename T>
void debug_out(const deque<T> &q) {
    size_t n = q.size();
    cerr << "[";
    for (size_t i = 0; i < n; ++i) {
        if (i != 0) cerr << ", ";
        debug_out(q[i]);
    }
    cerr << "]";
}

template<typename T>
void debug_out(stack<T> s) {
    vector<T> v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }
    reverse(v.begin(), v.end());
    int n = v.size();
    cerr << "[";
    for (int i = 0; i < n; ++i) {
        if (i != 0) cerr << ", ";
        debug_out(v[i]);
    }
    cerr << "]";
}

template<typename T>
void debug_out(queue<T> q) {
    cerr << "[";
    while (!q.empty()) {
        debug_out(q.front());
        q.pop();
        if (!q.empty()) cerr << ", ";
    }
    cerr << "]";
}

template<typename T, typename S, typename C>
void debug_out(priority_queue<T, S, C> q) {
    cerr << "[";
    while (!q.empty()) {
        debug_out(q.top());
        q.pop();
        if (!q.empty()) cerr << ", ";
    }
    cerr << "]";
}

template<typename T>
void debug_out(const set<T> &s) {
    cerr << "{";
    for (auto p = s.begin(); p != s.end(); ++p) {
        if (p != s.begin()) cerr << ", ";
        debug_out(*p);
    }
    cerr << "}";
}

template<typename T>
void debug_out(const multiset<T> &s) {
    cerr << "{";
    for (auto p = s.begin(); p != s.end(); ++p) {
        if (p != s.begin()) cerr << ", ";
        debug_out(*p);
    }
    cerr << "}";
}

template<typename K, typename V>
void debug_out(const map<K, V> &d) {
    cerr << "{";
    for (auto p = d.begin(); p != d.end(); ++p) {
        if (p != d.begin()) cerr << ", ";
        debug_out(p->first);
        cerr << ": ";
        debug_out(p->second);
    }
    cerr << "}";
}

template<typename K, typename V>
void debug_out(const unordered_map<K, V> &d) {
    cerr << "{";
    for (auto p = d.begin(); p != d.end(); ++p) {
        if (p != d.begin()) cerr << ", ";
        debug_out(p->first);
        cerr << ": ";
        debug_out(p->second);
    }
    cerr << "}";
}

template<typename T, typename U>
void debug_out(const pair<T, U> &p) {
    cerr << "(";
    debug_out(p.first);
    cerr << ", ";
    debug_out(p.second);
    cerr << ")";
}

template<size_t I, typename... Ts>
void debug_out_tuple(const tuple<Ts...> &t) {
    if constexpr (I < sizeof...(Ts)) {
        if constexpr (I != 0) {
            cerr << ", ";
        }
        debug_out(get<I>(t));
        debug_out_tuple<I + 1, Ts...>(t);
    }
}

template<typename... Ts>
void debug_out(const tuple<Ts...> &t) {
    cerr << "(";
    debug_out_tuple<0, Ts...>(t);
    cerr << ")";
}

void multiple_debug_out() {
}

template<typename T, typename... Ts>
void multiple_debug_out(T &&x, Ts &&...args) {
    debug_out(forward<T>(x));
    if constexpr (sizeof...(args)) cerr << " ";
    multiple_debug_out(forward<Ts>(args)...);
}

}  // namespace local_debug

#endif  // CP_TEMPLATES_DEBUG_HPP
