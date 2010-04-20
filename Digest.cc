//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit (c)
//
// file          /home/mycure/infinit/libraries/elle/cryptography/Digest.cc
//
// created       julien quintard   [mon feb  2 22:22:12 2009]
// updated       julien quintard   [mon apr 19 19:43:31 2010]
//

//
// ---------- includes --------------------------------------------------------
//

#include <elle/cryptography/Digest.hh>

namespace elle
{
  using namespace core;
  using namespace miscellaneous;
  using namespace archive;

  namespace cryptography
  {

//
// ---------- definitions -----------------------------------------------------
//

    ///
    /// this defines a null digest.
    ///
    const Digest		Digest::Null;

//
// ---------- entity ----------------------------------------------------------
//

    ///
    /// this method check if two digests match.
    ///
    Boolean		Digest::operator==(const Digest&	element) const
    {
      enter();

      // check the address as this may actually be the same object.
      if (this == &element)
	true();

      // compare the regions.
      if (this->region != element.region)
	false();

      true();
    }

    ///
    /// this macro-function call generates the entity.
    ///
    embed(Entity, Digest);

//
// ---------- dumpable --------------------------------------------------------
//

    ///
    /// this method dumps the digest.
    ///
    Status		Digest::Dump(const Natural32		margin) const
    {
      String		alignment(margin, ' ');

      enter();

      // display depending on the value.
      if (*this == Digest::Null)
	{
	  std::cout << alignment << "[Digest] Null" << std::endl;
	}
      else
	{
	  std::cout << alignment << "[Digest]" << std::endl;

	  // dump the region.
	  if (this->region.Dump(margin + 2) == StatusError)
	    escape("unable to dump the region");
	}

      leave();
    }

//
// ---------- archivable ------------------------------------------------------
//

    ///
    /// this method serializes a digest object.
    ///
    Status		Digest::Serialize(Archive&		archive) const
    {
      enter();

      // serialize the region.
      if (archive.Serialize(this->region) == StatusError)
	escape("unable to serialize the region");

      leave();
    }

    ///
    /// this method extracts a digest object.
    ///
    Status		Digest::Extract(Archive&		archive)
    {
      enter();

      // extract the content.
      if (archive.Extract(this->region) == StatusError)
	escape("unable to extract the region");

      leave();
    }

  }
}
