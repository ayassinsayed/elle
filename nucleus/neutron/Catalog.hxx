#ifndef  NUCLEUS_NEUTRON_CATALOG_HXX
# define NUCLEUS_NEUTRON_CATALOG_HXX

# include <cassert>

# include <elle/serialize/ArchiveSerializer.hxx>

ELLE_SERIALIZE_SIMPLE(nucleus::neutron::Catalog,
                      archive,
                      value,
                      version)
{
  assert(version == 0);

  archive & value.range;
}

#endif
