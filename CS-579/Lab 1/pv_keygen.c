#include "pv.h"

void
write_skfile (const char *skfname, void *raw_sk, size_t raw_sklen)
{
  int fdsk = 0;
  char *s = NULL;
  int status = 0;

  /* armor the raw symmetric key in raw_sk using armor64 */

  /* YOUR CODE HERE */

  /* now let's write the armored symmetric key to skfname */

  if ((fdsk = open (skfname, O_WRONLY|O_TRUNC|O_CREAT, 0600)) == -1) {
    perror (getprogname ());
    free (s);

    /* scrub the buffer that's holding the key before exiting */

    /* YOUR CODE HERE */

    exit (-1);
  }
  else {
    status = write (fdsk, s, strlen (s));
    if (status != -1) {
      status = write (fdsk, "\n", 1);
    }
    free (s);
    close (fdsk);
    /* do not scrub the key buffer under normal circumstances
       (it's up to the caller) */ 

    if (status == -1) {
      printf ("%s: trouble writing symmetric key to file %s\n", 
	      getprogname (), skfname);
      perror (getprogname ());
      
    /* scrub the buffer that's holding the key before exiting */

    /* YOUR CODE HERE */
      
      exit (-1);
    }
  }
}

void 
usage (const char *pname)
{
  printf ("Personal Vault: Symmetric Key Generation\n");
  printf ("Usage: %s SK-FILE \n", pname);
  printf ("       Generates a new symmetric key, and writes it to\n");
  printf ("       SK-FILE.  Overwrites previous file content, if any.\n");

  exit (1);
}

int 
main (int argc, char **argv)
{
  /* YOUR CODE HERE */

  if (argc != 2) {
    usage (argv[0]);
  }
  else {
    setprogname (argv[0]);

    /* first, let's create a new symmetric key */
    ri ();

    /* Note that since we'll need to do both AES-CTR and AES-CBC-MAC,
       there are actuall *two* symmetric keys, which could, e.g., be 
       stored contiguosly in a buffer */

    /* YOUR CODE HERE */

    /* now let's armor and dump to disk the symmetric key buffer */

    /* YOUR CODE HERE */

    /* finally, let's scrub the buffer that held the random bits 
       by overwriting with a bunch of 0's */

  }

  return 0;
}

