FROM python:3.9
 
RUN apt-get update
RUN apt-get install vim -y
RUN mkdir -p /home/struskawka
 
RUN pip install numpy

COPY dane.txt /home/struskawka/dane.txt 
COPY obw.py /home/struskawka/obw.py

WORKDIR /home/struskawka
# Run "
CMD ["python","/home/struskawka/obw.py"]
# CMD ["/bin/bash"]