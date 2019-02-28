import React from 'react';
import { Link } from 'react-router-dom';

export default (props) => {
  const { parent, onHamburgerClick } = props;
  return (
    <div id="wrapper">
      <div id="sidebar-wrapper">
        <ul className="sidebar-nav">
          <li className="sidebar-brand">
            <a href="#">Menu</a>
          </li>
          <li>
            <Link to="/" onClick={onHamburgerClick.bind(parent)}>Accueil</Link>
          </li>
          <li>
            <Link to="/about" onClick={onHamburgerClick.bind(parent)}>À Propos</Link>
          </li>
        </ul>
      </div>
    </div>
  )
};