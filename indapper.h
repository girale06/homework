#ifndef INDAPPER_H
#define INDAPPER_H

#include <list>
#include <string>
#include <vector>

template <typename Cont, typename T = typename Cont::value_type>
class index_appender_view
{
    private:
        
        std::list<Cont*> _allConts;
    
    public:
        index_appender_view() { }

        index_appender_view(index_appender_view<Cont, T>& other);

        ~index_appender_view() { }
        
        unsigned long size() const;

        void add(Cont& cont) ;

        T at(unsigned long ind_) const;
        
        T& operator[] (unsigned long ind_);
        
        const T& operator[](unsigned long ind) const;
        
};

template <typename Cont, typename T>
index_appender_view<Cont, T>::index_appender_view(index_appender_view<Cont, T>& other){
    for(Cont* c : other._allConts){
        _allConts.push_back(c);
    }
}

template <typename Cont, typename T>
unsigned long index_appender_view<Cont, T>::size() const {
    unsigned long res_ = 0;
    for (Cont* c : _allConts)
    {
        typename Cont::iterator iter_;
        for(iter_ = c->begin(); iter_ != c->end(); iter_++) res_++;
    }
    return res_;   
}

template <typename Cont, typename T>
void index_appender_view<Cont, T>::add(Cont& cont){
    _allConts.push_back(&cont);
}

template <typename Cont, typename T>
T index_appender_view<Cont, T>::at(unsigned long ind_) const{
    
    Cont* res_ = new Cont();
    for (Cont* co_ : _allConts)
    {
        if(ind_ + 1 > co_->size())
            ind_ -= co_->size();
        else{
            res_ = co_;
            break;
        }
    }
    return (*res_)[ind_];
}

template <typename Cont, typename T>
T& index_appender_view<Cont, T>::operator[] (unsigned long ind_)
{
    
    Cont* res_ = new Cont();
    for (Cont* co_ : _allConts)
    {
        if(ind_ + 1 > (*co_).size())
            ind_ -= (*co_).size();
        else{
            res_ = co_;
            break;
        }
    }
    return (*res_)[ind_];
}

template <typename Cont, typename T>
const T& index_appender_view<Cont, T>::operator[](unsigned long ind_) const
{
    
    Cont* res_ = new Cont();
    for (Cont* co_ : _allConts)
    {
        if(ind_ + 1 > (*co_).size())
            ind_ -= (*co_).size();
        else{
            res_ = co_;
            break;
        }
    }
    return const_cast<T&>((*res_)[ind_]);    
}

template<>
class index_appender_view<std::vector<bool>, bool>
{
    private:
        std::list<std::vector<bool>*> _allConts;
    public:
        index_appender_view() { }

        index_appender_view(index_appender_view<std::vector<bool>, bool>& other);
        
        unsigned long size() const;

        void add(std::vector<bool>& cont);

        bool at(unsigned long ind_) const;
        
        std::vector<bool>::reference operator[] (unsigned long ind_);
        
        const std::vector<bool>::reference operator[](unsigned long ind) const;
};

index_appender_view<std::vector<bool>, bool>::index_appender_view(index_appender_view<std::vector<bool>, bool>& other){
    for(std::vector<bool>* c : other._allConts){
        _allConts.push_back(c);
    }
}

void index_appender_view<std::vector<bool>, bool>::add(std::vector<bool>& cont){
    _allConts.push_back(&cont);
}

unsigned long index_appender_view<std::vector<bool>, bool>::size() const {
    unsigned long res_ = 0;
    for (std::vector<bool>* c : _allConts)
    {
        typename std::vector<bool>::iterator iter_;
        for(iter_ = c->begin(); iter_ != c->end(); iter_++) res_++;
    }
    return res_;   
}

bool index_appender_view<std::vector<bool>, bool>::at(unsigned long ind_) const{
    std::vector<bool>* res_ = new std::vector<bool>();
    for (std::vector<bool>* co_ : _allConts)
    {
        if(ind_ + 1 > co_->size())
            ind_ -= co_->size();
        else{
            res_ = co_;
            break;
        }
    }
    return (*res_).at(ind_);
}

std::vector<bool>::reference index_appender_view<std::vector<bool>, bool>::operator[] (unsigned long ind_)
{
    std::vector<bool>* res_ = new std::vector<bool>();
    for (std::vector<bool>* co_ : _allConts)
    {
        if(ind_ + 1 > co_->size())
            ind_ -= co_->size();
        else{
            res_ = co_;
            break;
        }
    }
    std::vector<bool>::reference refRes_ = res_->at(ind_);
    return refRes_;
}

const std::vector<bool>::reference index_appender_view<std::vector<bool>, bool>::operator[] (unsigned long ind_) const
{
    std::vector<bool>* res_ = new std::vector<bool>();
    for (std::vector<bool>* co_ : _allConts)
    {
        if(ind_ + 1 > co_->size())
            ind_ -= co_->size();
        else{
            res_ = co_;
            break;
        }
    }
    std::vector<bool>::reference refRes_ = res_->at(ind_);
    return refRes_;
}

#endif