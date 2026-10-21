# SCRATCH probe: can an SPC-signed WDM driver load on GitHub-hosted windows-latest without test signing?
# Verifies: build (xmake+WDK) -> sign with the blook-project SPC signer (XINDA cert + 2013 TSA) ->
# sc create/start -> STATE RUNNING -> user-mode client IOCTL -> stop/delete. Deleted after de-risking.
