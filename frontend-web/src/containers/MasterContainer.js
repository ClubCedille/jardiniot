import React, { Component } from 'react';
import { connect } from 'react-redux';
import Master from '../components/Master';

class MasterContainer extends Component {
  render() {
    return (
      <Master>
        <div className="page-content">
          {this.props.children}
        </div>
      </Master>
    );
  }
}

const mapStateToProps = (state) => {    
  return {};
};

const mapDispatchToProps = (dispatch) => {
  return {};
};

export default connect(mapStateToProps, mapDispatchToProps)(MasterContainer);