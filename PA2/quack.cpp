/**
 * @file quack.cpp
 * Implementation of the Quack class.
 *
 */

template <class T>
Quack<T>::Quack() {
    /**
     * @todo Your code here!
     * 
     */
    //vector<T> newVec(1);
    
    n1 = -1; // one to the left of left element of quack
    n2 = -1;  // right element side of quack
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */
template <class T>
void Quack<T>::push_right(T newItem) {
    /**
     * @todo Your code here!
     */
    data.push_back(newItem);
    n2++;
    //std::cout << "n1:" << n1 << std::endl;
    //std::cout << "n2:" << n2 << std::endl;
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */
template <class T>
T Quack<T>::pop_left() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (n1 == n2) {
        return T();
    }
 

    n1++;
    T item = data[n1];
    data[n1] = T();

    if ((n2 - n1) == (n1 + 1))
    {
        // resize to 1/2 of previous size
        //td::cout << "fn1:" << n1 << std::endl;
        //std::cout << "fn2:" << n2 << std::endl;

        int c = (n1 + 1);

        vector<T> temp(c);

        int n = 0;

        for (int i = n1 + 1; i <= n2; i++)
        {
            temp[n] = data[i];
            n++;
        }

        data.swap(temp); // coppies temp to data

        n2 = n2 - n1 - 1;
        n1 = -1;
    }

    return item;
}
/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::pop_right() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (n2 == n1)
    {
        return T();
    }

    if ((n2 - n1) == (n1 + 1))
    {
        // resize to 1/2 of previous size
        // td::cout << "fn1:" << n1 << std::endl;
        // std::cout << "fn2:" << n2 << std::endl;

        int c = (n1 + 1);

        vector<T> temp(c);

        int n = 0;

        for (int i = n1 + 1; i <= n2; i++)
        {
            temp[n] = data[i];
            n++;
        }

        data.swap(temp); // coppies temp to data

        n2 = n2 - n1 - 1;
        n1 = -1;
    }

    T item = data[n2];
    n2--;
    data.pop_back();
    //std::cout << "n1:" << n1 << std::endl;
    //std::cout << "n2:" << n2 << std::endl;

    return item;
}

/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike pop_left(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (n1 == n2)
    {
        return T();
    }
    T item = data[n1 + 1];
    return item;
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike pop_right(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (n2 == n1)
    {
        return T();
    }
    T item = data[n2];
    return item;
    
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::is_empty() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return (n2 == n1);
}
