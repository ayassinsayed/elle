#include <etoile/gear/Link.hh>
#include <etoile/gear/Nature.hh>

namespace etoile
{
  namespace gear
  {

//
// ---------- constructors & destructors --------------------------------------
//

    ///
    /// the constructor
    ///
    Link::Link():
      Object(NatureLink),

      contents(nullptr)
    {
    }

    ///
    /// the destructor
    ///
    Link::~Link()
    {
      // release the contents.
      if (this->contents != nullptr)
        delete this->contents;
    }

//
// ---------- dumpable --------------------------------------------------------
//

    ///
    /// this method dumps the contents along the the inherited object context.
    ///
    elle::Status        Link::Dump(const elle::Natural32        margin) const
    {
      elle::String      alignment(margin, ' ');

      std::cout << alignment << "[Link]" << std::endl;

      // dump the inherited object.
      if (Object::Dump(margin + 2) == elle::Status::Error)
        escape("unable to dump the inherited object");

      // dump the contents.
      if (this->contents != nullptr)
        {
          if (this->contents->Dump(margin + 4) == elle::Status::Error)
            escape("unable to dump the contents");
        }
      else
        {
          std::cout << alignment << elle::io::Dumpable::Shift
                    << "[Contents] " << elle::none << std::endl;
        }

      return elle::Status::Ok;
    }

  }
}
