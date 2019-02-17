import React, { Component } from 'react';
import { connect } from 'react-redux';
import MainPage from '../components/MainPage';

class MainPageContainer extends Component {
  render() {
    return <MainPage />;
  }
}

const mapStateToProps = (state) => {    
  return {};
};

const mapDispatchToProps = (dispatch) => {
  return {};
};

export default connect(mapStateToProps, mapDispatchToProps)(MainPageContainer);