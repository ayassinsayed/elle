//
// ---------- header ----------------------------------------------------------
//
// project       nucleus
//
// license       infinit
//
// file          /home/mycure/infinit/nucleus/neutron/Access.hh
//
// created       julien quintard   [thu mar  5 20:17:45 2009]
// updated       julien quintard   [sun may  8 09:08:20 2011]
//

#ifndef NUCLEUS_NEUTRON_ACCESS_HH
#define NUCLEUS_NEUTRON_ACCESS_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

#include <nucleus/proton/ContentHashBlock.hh>

#include <nucleus/neutron/State.hh>
#include <nucleus/neutron/Index.hh>
#include <nucleus/neutron/Size.hh>
#include <nucleus/neutron/Range.hh>
#include <nucleus/neutron/Subject.hh>
#include <nucleus/neutron/Record.hh>

namespace nucleus
{
  namespace neutron
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class represents an access control list.
    ///
    /// XXX \todo note that, for now, such a list is implemented through a
    /// single range. however the structure will be extended to an optimised
    /// general tree structure in a near future.
    ///
    class Access:
      public proton::ContentHashBlock
    {
    public:
      //
      // constructors & destructors
      //
      Access();

      //
      // methods
      //
      elle::Status	Add(Record*);
      elle::Status	Exist(const Subject&);
      elle::Status	Lookup(const Subject&,
			       Record*&);
      elle::Status	Consult(const Index&,
				const Size&,
				Range<Record>&) const;
      elle::Status	Upgrade(const elle::SecretKey&);
      elle::Status	Remove(const Subject&);
      elle::Status	Capacity(Size&) const;
      elle::Status	Locate(const Subject&,
			       Index&);
      elle::Status	Fingerprint(elle::Digest&) const;

      //
      // interfaces
      //

      // object
      declare(Access);

      // dumpable
      elle::Status	Dump(const elle::Natural32 = 0) const;

      // archivable
      elle::Status	Serialize(elle::Archive&) const;
      elle::Status	Extract(elle::Archive&);

      //
      // attributes
      //
      State		state;

      Range<Record>	range;
    };

  }
}

#endif
