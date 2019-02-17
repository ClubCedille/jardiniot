import React, { Component } from 'react';
import Header from './Header';
import Footer from './Footer';

export default class Master extends Component {
  render() {
    return (
      <div>
        <Header />

        <div className="content">
          {this.props.children}
        </div>
      </div>
    );
  }
}