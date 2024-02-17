/*!
  @file gob_adapter.hpp
  @brief Adapters for adding extended functions that combine public functions of existing classes
  @details Useful for adding functionality by combining simple functions of the original class.

  @mainpage gob_adapter

  Adapters for adding extended functions that combine public functions of existing classes
  - Can be encapsulated by classifying an ordinary function that uses the original class.
  - Does not modify the source code of the original class
  - "has-a" so there are no side effects on the original class (does not cause problems due to inheritance)
  - The use of arrow and dot operators is a little confusing, but it makes the difference between the original class function and a call to your own function clear.
  - Little impact from changes in the original class

  @author GOB <br>
  https://x.com/gob_52_gob <br>
  https://bsky.app/profile/gob52gob.bsky.social

  @copyright 2024 GOB
  @copyright Licensed under the MIT license. See LICENSE file in the project root for full license information.

*/
#ifndef GOBLLIB_ADAPTER_HPP
#define GOBLLIB_ADAPTER_HPP

#include <type_traits>

/*!
  @namespace goblib
  @brief Top level namespace of mine
 */
namespace goblib {
/*!
  @namespace plugin
  @brief Namespace for categorization
 */
namespace plugin {

/*!
  @class Adapter
  @brief Adapters for adding extension functions to existing classes
  @details A pointer to the original instance is maintained by so-called "has-a".
  @tparam CLS Class of arguments passed to the constructor
  @note Note that only public functions of existing classes can be called.
  @note Add your own class functions by inheriting from this class (This is abstract class)
  @warning Be aware of the life expectancy of the original instance.
*/
template<class CLS> class Adapter
{
  public:
    using class_type = typename std::remove_reference<CLS>::type; //!< @brief Class type (alias) of the argument passed to the constructor.

    ///@name Constructor
    ///@{
    Adapter() = delete; //!< @brief Default constructor(deleted)
    explicit Adapter(class_type* cls) : _cls(cls)  {} //!< @brief Pass pointer
    explicit Adapter(class_type& cls) : _cls(&cls) {} //!< @brief Pass reference
    ///@}
    virtual ~Adapter() = 0;

    explicit inline operator class_type*() { return _cls; } //!< @brief Cast operator

    ///@name Arrow operator
    ///@brief Call a function of the original class instance via this operator
    ///@{
    inline const class_type* operator->() const noexcept { return _cls; } //!< @brief const operator
    inline class_type* operator->() noexcept { return _cls; } //!< @brief non-const operator
    ///@}
    
  protected:
    class_type* _cls;
};
template<class CLS> Adapter<CLS>::~Adapter() {}
//
}}
#endif
