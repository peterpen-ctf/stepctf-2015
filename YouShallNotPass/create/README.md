   To create the task use follow steps:

0. Open project in Idea IntelliJ, run package option in maven's "pom.xml" file to generate YouShallNotPass.war (will be in target folder):

1. Check "setenv.sh, YouShallNotPass.war, ysnp.sh, Dockerfile" files are situated in the same folder.

2. Run run.sh in ysnp_mariadb to start Maria DB in docker for ysnp project.
  `bash run.sh`
  
3. Run ysnp.sh to deploy service in docker:
  `bash ysnp.sh`
  
4. Service will be running on 8080 inner port!

5. Use nginx's docker link to deploy task.