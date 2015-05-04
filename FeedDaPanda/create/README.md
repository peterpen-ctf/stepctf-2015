   To create the task use follow steps:

0. Open project in Idea IntelliJ, run package option in maven's "pom.xml" file to generate FeedDaPanda.war (will be in target folder):

1. Check "setenv.sh, FeedDaPande.war, feeddapanda.sh, dockerfile" files are situated in the same folder.
  
2. Run feeddapanda.sh to deploy service in docker:
  `bash feeddapanda.sh`
  
3. Service will be running on 13371 port.