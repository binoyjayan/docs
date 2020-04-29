FROM debian:latest
MAINTAINER binoy@example.com

# 1. Run
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -yq apt-utils
RUN DEBIAN_FRONTEND=noninteractive apt-get install -yq htop
RUN apt-get clean

# 2. CMD
# CMD [ "htop" ]
# CMD [ "ls", "-l" ]
# CMD [ "/bin/bash" ]

# 3. WORKDIR, ENV
WORKDIR /root
ENV MYROOT /root

# 4. ADD
ADD run.sh /root/run.sh
# CMD [ "./run.sh", "hello world" ]

# 5. Entry point - Non overridable commands run at startup
# ENTRYPOINT [ "./run.sh" ]
# CMD [ "arg1", "arg2" ]




