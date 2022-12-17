#ifndef INDAPPER_H
#define INDAPPER_H

#include <list>

template <typename Cont, typename T = typename Cont::value_type>
class index_appender_view
{
    private:
        std::list<Cont*> _allConts;
        typedef typename Cont::reference reference;
        typedef typename Cont::const_reference const_reference;
    
    public:

        index_appender_view() { }
        
        unsigned long size() const
        {
            unsigned long res_ = 0;
            for (Cont* c : _allConts)
            {
                typename Cont::iterator iter_;
                for(iter_ = c->begin(); iter_ != c->end(); iter_++) res_++;
            }
            return res_;   
        }

        void add(Cont& cont)
        {
            _allConts.push_back(&cont);
        }

        const_reference at(unsigned long ind_) const
        {
            Cont* res_ = new Cont();
            for (Cont* co_ : _allConts)
            {
                if(ind_ + 1 > co_->size())
                    ind_ -= co_->size();
                else
                {
                    res_ = co_;
                    break;
                }
            }
            return (*res_)[ind_];
        }
        
        reference operator[] (unsigned long ind_)
        {
            Cont* res_ = new Cont();
            for (Cont* co_ : _allConts)
            {
                if(ind_ + 1 > (*co_).size())
                    ind_ -= (*co_).size();
                else
                {
                    res_ = co_;
                    break;
                }
            }
            return (*res_)[ind_];
        }
        
        const_reference operator[](unsigned long ind) const
        {
            return at(ind);
        }
        
};

#endif
