/*
* Assignment 2: HashMap template implementation (STARTER CODE)
*      TODO: write a comment here.
*/

#include "hashmap.h"

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap() : 
    HashMap{kDefaultBuckets} { }

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(size_t bucket_count, const H& hash) :
    _size{0},
    _hash_function{hash},
    _buckets_array(bucket_count, nullptr) { }


template <typename K, typename M, typename H>
HashMap<K, M, H>::~HashMap() {
    clear();
}

template <typename K, typename M, typename H>
inline size_t HashMap<K, M, H>::size() {
    return _size;
}
//add
template <typename K, typename M, typename H>
inline size_t HashMap<K, M, H>::size() const {
    return _size;//这里就完全没必要再用static_cast/const_cast的trick了
}
//end

template <typename K, typename M, typename H>
inline bool HashMap<K, M, H>::empty() {
    return size() == 0;
}

//add
template <typename K, typename M, typename H>
inline bool HashMap<K, M, H>::empty() const
{
    return const_cast<HashMap<K, M, H> *>(this)->empty();
}
//end

template <typename K, typename M, typename H>
inline float HashMap<K, M, H>::load_factor() {
    return static_cast<float>(size())/bucket_count();
};

template <typename K, typename M, typename H>
inline size_t HashMap<K, M, H>::bucket_count() const{
    return _buckets_array.size();
};

template <typename K, typename M, typename H>
M& HashMap<K, M, H>::at(const K& key) {
    auto [prev, node_found] = find_node(key);
            if (node_found == nullptr) {
        throw std::out_of_range("HashMap<K, M, H>::at: key not found");
    }
    return node_found->value.second;
}

//add 
template <typename K, typename M, typename H>
const M& HashMap<K, M, H>::at(const K& key) const {
   return static_cast<const M&>(const_cast<HashMap<K, M, H>*>(this)->at(key));
}
//end

template <typename K, typename M, typename H>
bool HashMap<K, M, H>::contains(const K& key) {
    return find_node(key).second != nullptr;
}
//add 
template <typename K, typename M, typename H>
bool   HashMap<K, M, H>::contains(const K& key) const {
    return find_node(key).second != nullptr;
}
//end

template <typename K, typename M, typename H>
void HashMap<K, M, H>::clear() {
    for (auto& curr : _buckets_array) {
        while (curr != nullptr) {
            curr = curr->next;
        }
    }
    _size = 0;
}

template <typename K, typename M, typename H>
typename HashMap<K, M, H>::iterator HashMap<K, M, H>::find(const K& key) {
    return make_iterator(find_node(key).second);
}

//add 
template <typename K, typename M, typename H>
typename HashMap<K, M, H>::const_iterator HashMap<K, M, H>::find(const K& key) const {
    return static_cast<const_iterator>(const_cast<HashMap<K, M, H>*>(this)->find(key));
}
//end



template <typename K, typename M, typename H>
std::pair<typename HashMap<K, M, H>::iterator, bool> HashMap<K, M, H>::insert(const value_type& value) {
    const auto& [key, mapped] = value;
    auto [prev, node_to_edit] = find_node(key);
    //这里的index似乎没有考虑发生hash冲突的情况？？

    //这里的_hash_function是HashMap的一个private属性
    size_t index = _hash_function(key) % bucket_count();

    //按照预期，node_to_edit应该是空指针
    if (node_to_edit != nullptr) {
        return {make_iterator(node_to_edit), false};
    }

    auto temp = new node(value, _buckets_array[index]);
    _buckets_array[index] = temp;

    ++_size;
    return {make_iterator(temp), true};
}

template <typename K, typename M, typename H>
typename HashMap<K, M, H>::node_pair HashMap<K, M, H>::find_node(const K& key) const {
    size_t index = _hash_function(key) % bucket_count();
    node* curr = _buckets_array[index];
    node* prev = nullptr; // if first node is the key, return {nullptr, front}
    while (curr != nullptr) {
        const auto& [found_key, found_mapped] = curr->value;
        if (found_key == key) {
            return {prev, curr};
        }
        prev = curr;
        curr = curr->next;
    }
    return {nullptr, nullptr}; // key not found at all.
}


//一个使用const的example
template <typename K, typename M, typename H>
typename HashMap<K, M, H>::iterator HashMap<K, M, H>::begin() {
    size_t index = first_not_empty_bucket();
    if (index == bucket_count()) {
        return end();
    }
    return make_iterator(_buckets_array[index]);
}

//注意函数中const关键字的使用
template <typename K, typename M, typename H>
typename HashMap<K, M, H>::const_iterator HashMap<K, M, H>::begin() const {
    // This is called the static_cast/const_cast trick, which allows us to reuse
    // the non-const version of find to implement the const version.
    // The idea is to cast this so it's pointing to a non-const HashMap, which
    // calls the overload above (and prevent infinite recursion).
    // Also note that we are calling the conversion operator in the iterator class!

    //这是不是有点类似于委托构造函数的用法
    return static_cast<const_iterator>(const_cast<HashMap<K, M, H>*>(this)->begin());
}

template <typename K, typename M, typename H>
typename HashMap<K, M, H>::iterator HashMap<K, M, H>::end() {
    return make_iterator(nullptr);
}

//add 
template <typename K, typename M, typename H>
typename HashMap<K, M, H>::const_iterator HashMap<K, M, H>::end() const {
    return static_cast<const_iterator>(const_cast<HashMap<K, M, H>*>(this)->end());
}
//end


template <typename K, typename M, typename H>
size_t HashMap<K, M, H>::first_not_empty_bucket() const {
    auto isNotNullptr = [](const auto& v){
        return v != nullptr;
    };

    auto found = std::find_if(_buckets_array.begin(), _buckets_array.end(), isNotNullptr);
    return found - _buckets_array.begin();
}

template <typename K, typename M, typename H>
typename HashMap<K, M, H>::iterator HashMap<K, M, H>::make_iterator(node* curr) {
    if (curr == nullptr) {
        return {&_buckets_array, curr, bucket_count()};
    }
    size_t index = _hash_function(curr->value.first) % bucket_count();
    return {&_buckets_array, curr, index};
}

template <typename K, typename M, typename H>
bool HashMap<K, M, H>::erase(const K& key) {
    auto [prev, node_to_erase] = find_node(key);
    if (node_to_erase == nullptr) {
        return false;
    }
    size_t index = _hash_function(key) % bucket_count();
    (prev ? prev->next : _buckets_array[index]) = node_to_erase->next;
    --_size;
    return true;
}

template <typename K, typename M, typename H>
typename HashMap<K, M, H>::iterator HashMap<K, M, H>::erase(typename HashMap<K, M, H>::const_iterator pos) {
    erase(pos++->first);
    return make_iterator(pos._node); // unfortunately we need a regular iterator, not a const_iterator
}

template <typename K, typename M, typename H>
    void HashMap<K, M, H>::debug() {
    std::cout << std::setw(30) << std::setfill('-') << '\n' << std::setfill(' ')
          << "Printing debug information for your HashMap implementation\n"
          << "Size: " << size() << std::setw(15) << std::right
          << "Buckets: " << bucket_count() << std::setw(20) << std::right
          << "(load factor: " << std::setprecision(2) << load_factor() << ") \n\n";

    for (size_t i = 0; i < bucket_count(); ++i) {
        std::cout << "[" << std::setw(3) << i << "]:";
        node* curr = _buckets_array[i];
        while (curr != nullptr) {
            const auto& [key, mapped] = curr->value;
            // next line will not compile if << not supported for K or M
            std::cout <<  " -> " << key << ":" << mapped;
            curr = curr->next;
        }
        std::cout <<  " /" <<  '\n';
    }
    std::cout << std::setw(30) << std::setfill('-') << '\n' << std::setfill(' ');
}

template <typename K, typename M, typename H>
void HashMap<K, M, H>::rehash(size_t new_bucket_count) {
if (new_bucket_count == 0) {
    throw std::out_of_range("HashMap<K, M, H>::rehash: new_bucket_count must be positive.");
}

std::vector<node*> new_buckets_array(new_bucket_count, nullptr);
    for (auto& curr : _buckets_array) { // short answer question is asking about this 'curr'
        while (curr != nullptr) {
            const auto& [key, mapped] = curr->value;
            size_t index = _hash_function(key) % new_bucket_count;

            auto temp = curr;
            curr = temp->next;
            temp->next = new_buckets_array[index];
            new_buckets_array[index] = temp;
        }
    }
    _buckets_array = std::move(new_buckets_array);
}

template <typename K, typename M, typename H>
template <typename InputIt>
HashMap<K, M, H>::HashMap(InputIt first, InputIt last, size_t bucket_count, const H& hash) :
   HashMap(bucket_count, hash) {
   for (auto iter = first; iter != last; ++iter) {
      insert(*iter);
   }
}

template <typename K, typename M, typename H>
HashMap<K, M, H>::HashMap(std::initializer_list<value_type> init, size_t bucket_count, const H& hash) :
   HashMap{init.begin(), init.end(), bucket_count, hash} {
}

template <typename K, typename M, typename H>
M& HashMap<K, M, H>::operator[](const K& key) {
   return insert({key, {}}).first->second;
}

template <typename K, typename M, typename H>
bool operator==(const HashMap<K, M, H>& lhs, const HashMap<K, M, H>& rhs) {
   return lhs.size() == rhs.size() && std::is_permutation(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename K, typename M, typename H>
bool operator!=(const HashMap<K, M, H>& lhs, const HashMap<K, M, H>& rhs) {
   return !(lhs == rhs);
}

template <typename K, typename M, typename H>
std::ostream& operator<<(std::ostream& os, const HashMap<K, M, H>& rhs) {
   std::ostringstream oss("{", std::ostringstream::ate);    
   for (const auto& [key, value] : rhs) {
       oss << key << ":" << value << ", ";
   }
   std::string s = oss.str();
   os << s.substr(0, s.length()-2) << "}";
   return os;
}

/* Begin Milestone 2: Special Member Functions */

//四个符合stl标准类的特殊函数

//首先是复制构造函数 --当然是要深拷贝啦
// template <typename K, typename M, typename H>
// HashMap<K,M,H>::HashMap(const HashMap<K,M,H>& other){
//     this->_size=other._size;
//     //this->_hash_function=other->_hash_function;
//     //你直接这样copy是会出错的！这种意识应该要有，或者说，对于copy函数，这才是你该记的
//     //copy(other->_buckets_array.begin(),other->_buckets_array.end(),_buckets_array.begin)

//     //是时候展现adaptor的威力了！
//     copy(other._buckets_array.begin(),other._buckets_array.end(),back_inserter(this->_buckets_array));


// }

template <typename K, typename M, typename H>
HashMap<K,M,H>::HashMap(const HashMap<K,M,H>& other):HashMap(other.bucket_count(),other._hash_function){
    //这里要掌握自动遍历语法的本质：本质上是调用该容器的迭代器
    for(auto [key,value]:other){
        insert(std::make_pair(key,value));
    }

}
//然后是赋值构造函数
template <typename K, typename M, typename H>

HashMap<K,M,H>& HashMap<K,M,H>::operator=(const HashMap<K,M,H>& other){
    if(this!=&other){
        clear();
        for(auto [key,value]:other){
            insert(make_pair(key,value));
        }
        return *this;
    }
    return *this;
}

//好好好，这种活学活用的感觉好快乐！


//====================my wrong version  begin==============
//下面是move构造函数
// template <typename K, typename M, typename H>
// HashMap<K,M,H>::HashMap(HashMap<K,M,H>&& other){
//     //this->_size=std::move(other->_size);
//     this->_size=other._size;
//     this->_hash_function=std::move(other._hash_function);
//     this->_buckets_array=std::move(other._buckets_array);
//     //other.clear();
// }

//move赋值函数


// template <typename K, typename M, typename H>
// HashMap<K,M,H>& HashMap<K,M,H>::operator=(HashMap<K,M,H>&& other){
//      if (&other != this) {
//         clear(); // 可能还需要执行其他的清理操作
//         this->_size = other._size;
//         this->_hash_function = std::move(other._hash_function);
//         this->_buckets_array = std::move(other._buckets_array);
//         // 不需要再手动清理 other，因为资源已经在移动操作中正确处理了
//     }
//     return *this;
// }



//================my wrong version end(originally wrong ,now ok)========================
template <typename K, typename M, typename H>
HashMap<K,M,H>::HashMap(HashMap<K,M,H>&& other):
_size{std::move(other._size)},
_hash_function{std::move(other._hash_function)},
_buckets_array{other.bucket_count(), nullptr}
//这里我假设了STL_vector提供了与之对应的move semantics
//楼上是小丑🤣🤣🤣
{
    _buckets_array.resize(other.bucket_count());
    for(size_t i=0;i<other.bucket_count();i++){
        _buckets_array[i]=std::move(other._buckets_array[i]);
        other._buckets_array[i]=nullptr;
    }
    other._size=0;
}


template <typename K, typename M, typename H>
 HashMap<K,M,H>& HashMap<K,M,H>::operator=(HashMap<K,M,H>&& other)
 {
    if(&other==this) return *this;
    clear();
    _size=std::move(other._size);
     _hash_function = std::move(other._hash_function);
     //下面这种方法使不得
    //_buckets_array=std::move(other._buckets_array);
    _buckets_array.resize(other.bucket_count());
    for (size_t i = 0; i < other.bucket_count(); i++) {
            _buckets_array[i] = std::move(other._buckets_array[i]);
            other._buckets_array[i] = nullptr;
        }

    //other._size=0;

    return *this;
 }
// move assignment operator
// template <typename K, typename M, typename H>
// HashMap<K, M, H>& HashMap<K, M, H>::operator=(HashMap&& rhs) {
//     if (this != &rhs) {
//         clear();
//         _size = std::move(rhs._size);
//         _hash_function = std::move(rhs._hash_function);
//         _buckets_array.resize(rhs.bucket_count());
//         for (size_t i = 0; i < rhs.bucket_count(); i++) {
//             _buckets_array[i] = std::move(rhs._buckets_array[i]);
//             rhs._buckets_array[i] = nullptr;
//         }
//         rhs._size = 0;
//     }
//     return *this;
// }


/* end student code */
