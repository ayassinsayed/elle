//
// ---------- header ----------------------------------------------------------
//
// project       nucleus
//
// license       infinit
//
// file          /home/mycure/infinit/nucleus/proton/ImprintBlock.cc
//
// created       julien quintard   [sat may  7 23:41:32 2011]
// updated       julien quintard   [sun may  8 09:30:07 2011]
//

//
// ---------- includes --------------------------------------------------------
//

#include <nucleus/proton/ImprintBlock.hh>
#include <nucleus/proton/Family.hh>

namespace nucleus
{
  namespace proton
  {

//
// ---------- constructors & destructors --------------------------------------
//

    ///
    /// default constructor.
    ///
    ImprintBlock::ImprintBlock():
      Block(FamilyImprintBlock)
    {
    }

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method creates an OKB based on the given owner's public key.
    ///
    elle::Status	ImprintBlock::Create(const elle::PublicKey& owner)
    {
      enter();

      // retrieve the current time.
      if (this->seed.stamp.Current() == elle::StatusError)
	escape("unable to retrieve the current time");

      // generate a random number.
      this->seed.salt = (elle::Natural64)::rand();

      // set the owner public key.
      this->owner.K = owner;

      // create a subject corresponding to the user. note that this
      // subject will never be serialized hence is not really part of
      // the object but is used to ease the process of access control.
      if (this->owner.subject.Create(this->owner.K) == elle::StatusError)
	escape("unable to create the owner subject");

      leave();
    }

    ///
    /// this method computes the block's address.
    ///
    elle::Status	ImprintBlock::Bind(Address&		address)
      const
    {
      enter();

      // compute the address.
      if (address.Create(this->network,
			 this->seed.stamp,
			 this->seed.salt,
			 this->owner.K) == elle::StatusError)
	escape("unable to compute the OKB's address");

      leave();
    }

    ///
    /// this method verifies the block's validity.
    ///
    elle::Status	ImprintBlock::Validate(const Address&	address)
      const
    {
      Address		self;

      enter();

      //
      // make sure the address has not be tampered and correspond to the
      // hash of the tuple (stamp, salt, owner public key).
      //

      // compute the address.
      if (self.Create(this->network,
		      this->seed.stamp,
		      this->seed.salt,
		      this->owner.K) == elle::StatusError)
	escape("unable to compute the OKB's address");

      // verify with the recorded address.
      if (address != self)
	escape("the address does not correspond to the block's public key");

      true();
    }

//
// ---------- dumpable --------------------------------------------------------
//

    ///
    /// this function dumps an block object.
    ///
    elle::Status	ImprintBlock::Dump(const
					     elle::Natural32	margin) const
    {
      elle::String	alignment(margin, ' ');

      enter();

      std::cout << alignment << "[ImprintBlock]" << std::endl;

      // dump the parent class.
      if (Block::Dump(margin + 2) == elle::StatusError)
	escape("unable to dump the underlying block");

      // dump the stamp.
      std::cout << alignment << elle::Dumpable::Shift
		<< "[Stamp]" << std::endl;

      if (this->seed.stamp.Dump() == elle::StatusError)
	escape("unable to dump the stamp");

      // dump the salt.
      std::cout << alignment << elle::Dumpable::Shift
		<< "[Salt]" << this->seed.salt << std::endl;

      // dump the owner's public key.
      std::cout << alignment << elle::Dumpable::Shift
		<< "[Owner]" << std::endl;

      if (this->owner.K.Dump(margin + 4) == elle::StatusError)
	escape("unable to dump the owner's public key");

      leave();
    }

//
// ---------- archivable ------------------------------------------------------
//

    ///
    /// this method serializes the block object.
    ///
    elle::Status	ImprintBlock::Serialize(elle::Archive& archive) const
    {
      enter();

      // serialize the parent class.
      if (Block::Serialize(archive) == elle::StatusError)
	escape("unable to serialize the underlying block");

      // serialize the owner part.
      if (archive.Serialize(this->seed.stamp,
			    this->seed.salt,
			    this->owner.K) == elle::StatusError)
	escape("unable to serialize the block's content");

      leave();
    }

    ///
    /// this method extracts the block object.
    ///
    elle::Status	ImprintBlock::Extract(elle::Archive&	archive)
    {
      enter();

      // extract the parent class.
      if (Block::Extract(archive) == elle::StatusError)
	escape("unable to extract the underlying block");

      // check the family.
      if (this->family != FamilyImprintBlock)
	escape("invalid family");

      // extract the owner part.
      if (archive.Extract(this->seed.stamp,
			  this->seed.salt,
			  this->owner.K) == elle::StatusError)
	escape("unable to extract the block's content");

      // compute the owner subject.
      if (this->owner.subject.Create(this->owner.K) == elle::StatusError)
	escape("unable to create the owner subject");

      leave();
    }

  }
}
