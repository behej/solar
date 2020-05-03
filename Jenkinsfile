pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        echo 'Hello world'
      }
    }

    stage('') {
      steps {
        mail(subject: 'hello', body: 'test', to: 'jerome.behe@gmail.com')
      }
    }

  }
}