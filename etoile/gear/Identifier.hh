#ifndef ETOILE_GEAR_IDENTIFIER_HH
# define ETOILE_GEAR_IDENTIFIER_HH

# include <elle/types.hh>
# include <elle/radix/Object.hh>
# include <elle/Printable.hh>

# include <elle/idiom/Open.hh>

namespace etoile
{
  namespace gear
  {

    ///
    /// this class can be used to uniquely identify actors whose role is
    /// to act on scopes.
    ///
    class Identifier:
      public elle::radix::Object,
      public elle::Printable
    {
    public:
      //
      // constants
      //
      static const elle::Natural64      Zero;

      static const Identifier           Null;

      //
      // static attribute
      //
      static elle::Natural64            Counter;

      //
      // constructors & destructors
      //
      Identifier();

      //
      // methods
      //
      elle::Status              Generate();

      //
      // interfaces
      //

      // object
      declare(Identifier);
      elle::Boolean             operator==(const Identifier&) const;
      elle::Boolean             operator<(const Identifier&) const;

      // dumpable
      void
      print(std::ostream& out) const;
      elle::Status              Dump(const elle::Natural32 = 0) const;

      //
      // attributes
      //
      elle::Natural64           value;
    };

    std::ostream&
    operator << (std::ostream& stream, Identifier const& id);
  }
}

# include <etoile/gear/Identifier.hxx>

#endif
