#include <horizon/macosx/MacOSX.hh>
#include <horizon/macosx/Crux.hh>
#include <horizon/macosx/FUSE.hh>

#include <Infinit.hh>

#include <elle/idiom/Open.hh>

namespace horizon
{
  namespace macosx
  {

//
// ---------- definitions -----------------------------------------------------
//

    ///
    /// this variable contains the UID of the 'somebody' user, user which
    /// is used whenever the system cannot map the Infinit user on a local
    /// user.
    ///
    uid_t                               MacOSX::Somebody::UID;

    ///
    /// this variable contains the GID of the 'somebody' group.
    ///
    gid_t                               MacOSX::Somebody::GID;

    ///
    /// this varaible contains the mappings between local user/group
    /// identities and Infinit identities.
    ///
    lune::Dictionary                    MacOSX::Dictionary;

//
// ---------- methods ---------------------------------------------------------
//

    ///
    /// this method initializes MacOS X.
    ///
    elle::Status        MacOSX::Initialize()
    {
      //
      // initialize the 'somebody' entity.
      //
      {
        struct ::passwd*        passwd;

        // retrieve the passwd structure related to the user 'somebody'.
        // if nullptr, try to fallback to 'nobody'.
        if ((passwd = ::getpwnam("somebody")) == nullptr &&
            (passwd = ::getpwnam("nobody")) == nullptr)
          escape("it seems that the user 'somebody' does not exist");

        // set the uid and gid.
        MacOSX::Somebody::UID = passwd->pw_uid;
        MacOSX::Somebody::GID = passwd->pw_gid;
      }

      //
      // load the user/group maps which will be used to translate Infinit
      // user/group identifiers into local identifiers.
      //
      {
        // if the dictionary exist.
        if (MacOSX::Dictionary.Exist(Infinit::User) == elle::Status::True)
          {
            // load the dictionary file.
            if (MacOSX::Dictionary.Load(Infinit::User) == elle::Status::Error)
              escape("unable to load the dictionary");
          }
      }

      //
      // initialize FUSE.
      //
      {
        struct ::fuse_operations        operations;

        // set all the pointers to zero.
        ::memset(&operations, 0x0, sizeof (::fuse_operations));

        operations.statfs = Crux::Statfs;
        operations.getattr = Crux::Getattr;
        operations.fgetattr = Crux::Fgetattr;
        operations.utimens = Crux::Utimens;

        operations.opendir = Crux::Opendir;
        operations.readdir = Crux::Readdir;
        operations.releasedir = Crux::Releasedir;
        operations.mkdir = Crux::Mkdir;
        operations.rmdir = Crux::Rmdir;

        operations.access = Crux::Access;
        operations.chmod = Crux::Chmod;
        operations.chown = Crux::Chown;
#if defined(HAVE_SETXATTR)
        operations.setxattr = Crux::Setxattr;
        operations.getxattr = Crux::Getxattr;
        operations.listxattr = Crux::Listxattr;
        operations.removexattr = Crux::Removexattr;
#endif

        // operations.link: not supported
        operations.readlink = Crux::Readlink;
        operations.symlink = Crux::Symlink;

        operations.create = Crux::Create;
        // operations.mknod: not supported
        operations.open = Crux::Open;
        operations.write = Crux::Write;
        operations.read = Crux::Read;
        operations.truncate = Crux::Truncate;
        operations.ftruncate = Crux::Ftruncate;
        operations.release = Crux::Release;

        operations.rename = Crux::Rename;
        operations.unlink = Crux::Unlink;

        // the following flag being activated prevents the path argument
        // to be passed for functions which take a file descriptor.
        operations.flag_nullpath_ok = 1;

        // initialize FUSE.
        if (FUSE::Initialize(operations) == elle::Status::Error)
          escape("unable to initialize FUSE");
      }

      return elle::Status::Ok;
    }

    ///
    /// this method cleans MacOS X.
    ///
    elle::Status        MacOSX::Clean()
    {
      // clean FUSE.
      if (FUSE::Clean() == elle::Status::Error)
        escape("unable to clean FUSE");

      return elle::Status::Ok;
    }

  }
}
