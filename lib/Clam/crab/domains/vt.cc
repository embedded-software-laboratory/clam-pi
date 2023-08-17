
#include <clam/config.h>
#include <clam/CrabDomain.hh>
#include <clam/RegisterAnalysis.hh>
#include "vt.hh"


namespace clam {
#ifdef INCLUDE_ALL_DOMAINS
	REGISTER_DOMAIN(clam::CrabDomain::VARIABLE_TENDENCY, vt_domain)
#else
	UNREGISTER_DOMAIN(vt_domain)
#endif  
} // end namespace clam
