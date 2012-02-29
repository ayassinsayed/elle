//
// ---------- header ----------------------------------------------------------
//
// project       plasma/updater
//
// license       infinit
//
// author        Raphaël Londeix   [Fri 27 Jan 2012 11:54:35 AM CET]
//

#ifndef PLASMA_UPDATER_APPLICATION_HH
#define PLASMA_UPDATER_APPLICATION_HH

//
// ---------- includes --------------------------------------------------------
//

#include <string>

#include <QApplication>
#include <QProcess>

#include "IdentityUpdater.hh"
#include "ReleaseUpdater.hh"

namespace plasma {
  namespace updater {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// This class is in charge to download a file list.
    /// The file list uri is given to the ctor and downloaded. The downloader
    /// compares each file with its md5.
    /// XXX: add RSA signature instead of md5 hash ?
    ///
    class Application : public QApplication
    {
      Q_OBJECT

    private:
      struct IdCard
      {
          std::string token;
          std::string identity;
      };

    private:
      ReleaseUpdater  _releaseUpdater;
      IdentityUpdater _identityUpdater;
      QProcess        _watchdogProcess;
      IdCard          _idCard;

    public:
      Application(int ac, char** av);
      virtual ~Application();
      int Exec();
    private:
      bool _CheckInfinitHome();
    private slots:
      void _OnReleaseUpdated(bool);
      void _OnIdentityUpdated(std::string const& token,
                              std::string const& identity);
      void _OnWatchdogLaunched();
    };

  }
} //!plasma::updater

#endif /* ! DOWNLOADER_HH */

